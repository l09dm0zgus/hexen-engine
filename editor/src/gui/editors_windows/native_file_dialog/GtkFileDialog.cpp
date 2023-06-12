//
// Created by cx9ps3 on 12.06.2023.
//

#include <iostream>
#include "GtkFileDialog.h"

void edit::gui::GTKFileDialog::addFiltersToDialog(GtkWidget *dialog,const edit::gui::INativeFileDialog::FileFilter &fileFilter)
{
    GtkFileFilter *gtkFileFilter;
    gtkFileFilter = gtk_file_filter_new();
    for(auto &filter : fileFilter)
    {
        if (filter.second == "all")
        {
            gtk_file_filter_set_name( gtkFileFilter, filter.first.c_str());
            gtk_file_filter_add_pattern( gtkFileFilter, "*" );
        }
        else
        {
            std::vector<std::string> splittedStrings = splitString(filter.second,";");
            for(auto& str : splittedStrings)
            {
                std::string fileSpec;
                fileSpec.append("*.");
                fileSpec.append(str);

                gtk_file_filter_set_name( gtkFileFilter, filter.first.c_str());
                gtk_file_filter_add_pattern( gtkFileFilter, fileSpec.c_str());
            }
        }
    }
    gtk_file_chooser_add_filter( GTK_FILE_CHOOSER(dialog), gtkFileFilter );
}

void edit::gui::GTKFileDialog::setDefaultPath(GtkWidget *dialog, const std::string &defaultPath)
{
    gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER(dialog), defaultPath.c_str() );
}

edit::gui::INativeFileDialog::Status edit::gui::GTKFileDialog::allocatePathSet(GSList *fileList, edit::gui::INativeFileDialog::PathSet *pathSet)
{
    pathSet->count = g_slist_length( fileList );
    assert( pathSet->count > 0 );
    GSList *node;
    for ( node = fileList; node; node = node->next )
    {
        assert(node->data);
        pathSet->path.emplace_back((const gchar*)node->data);
    }
    g_slist_free( fileList );
    return Status::STATUS_OK;
}

void edit::gui::GTKFileDialog::waitForCleanUp()
{
    while (gtk_events_pending())
    {
        gtk_main_iteration();
    }
}

edit::gui::INativeFileDialog::Status edit::gui::GTKFileDialog::openDialog(const edit::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, std::string &pathToFile)
{
    GtkWidget *dialog;
    Status result;

    if ( !gtk_init_check(nullptr, nullptr) )
    {
        std::cout << "gtk_init_check failed to initilaize GTK+\n" ;
        return Status::STATUS_ERROR;
    }

    dialog = gtk_file_chooser_dialog_new( "Open File", nullptr,GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel", GTK_RESPONSE_CANCEL,"_Open", GTK_RESPONSE_ACCEPT,nullptr );

    /* Build the filter list */
    addFiltersToDialog(dialog, filterList);

    /* Set the default path */
    setDefaultPath(dialog, defaultPath);

    result = Status::STATUS_CANCEL;
    if ( gtk_dialog_run( GTK_DIALOG(dialog) ) == GTK_RESPONSE_ACCEPT )
    {
        pathToFile = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );

        result = Status::STATUS_OK;
    }

    waitForCleanUp();
    gtk_widget_destroy(dialog);
    waitForCleanUp();

    return result;
}

edit::gui::INativeFileDialog::Status edit::gui::GTKFileDialog::openDialog(const edit::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, PathSet *pathToFiles)
{
    GtkWidget *dialog;
    Status result;

    if ( !gtk_init_check(nullptr, nullptr) )
    {
        std::cout << "gtk_init_check failed to initilaize GTK+\n" ;
        return Status::STATUS_ERROR;
    }

    dialog = gtk_file_chooser_dialog_new( "Open Files", nullptr,GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel", GTK_RESPONSE_CANCEL,"_Open", GTK_RESPONSE_ACCEPT,nullptr );
    gtk_file_chooser_set_select_multiple( GTK_FILE_CHOOSER(dialog), TRUE );

    /* Build the filter list */
    addFiltersToDialog(dialog, filterList);

    /* Set the default path */
    setDefaultPath(dialog, defaultPath);

    result = Status::STATUS_CANCEL;
    if ( gtk_dialog_run( GTK_DIALOG(dialog) ) == GTK_RESPONSE_ACCEPT )
    {
        GSList *fileList = gtk_file_chooser_get_filenames( GTK_FILE_CHOOSER(dialog) );

        if ( allocatePathSet( fileList, pathToFiles ) == Status::STATUS_ERROR )
        {
            gtk_widget_destroy(dialog);
            return Status::STATUS_ERROR;
        }

        result = Status::STATUS_OK;
    }

    waitForCleanUp();
    gtk_widget_destroy(dialog);
    waitForCleanUp();

    return result;
}

edit::gui::INativeFileDialog::Status edit::gui::GTKFileDialog::saveDialog(const edit::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, std::string &pathToFile)
{
    GtkWidget *dialog;
    Status result;

    if ( !gtk_init_check(nullptr, nullptr) )
    {
        std::cout << "gtk_init_check failed to initilaize GTK+\n" ;
        return Status::STATUS_ERROR;
    }

    dialog = gtk_file_chooser_dialog_new( "Save File", nullptr,GTK_FILE_CHOOSER_ACTION_SAVE,"_Cancel", GTK_RESPONSE_CANCEL,"_Save", GTK_RESPONSE_ACCEPT,nullptr );
    gtk_file_chooser_set_do_overwrite_confirmation( GTK_FILE_CHOOSER(dialog), TRUE );
    /* Build the filter list */
    addFiltersToDialog(dialog, filterList);

    /* Set the default path */
    setDefaultPath(dialog, defaultPath);

    result = Status::STATUS_CANCEL;
    if ( gtk_dialog_run( GTK_DIALOG(dialog) ) == GTK_RESPONSE_ACCEPT )
    {
        pathToFile = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );

        result = Status::STATUS_OK;
    }

    waitForCleanUp();
    gtk_widget_destroy(dialog);
    waitForCleanUp();

    return result;
}

edit::gui::INativeFileDialog::Status edit::gui::GTKFileDialog::pickDialog(const std::string &defaultPath, std::string &pathToFile)
{
    GtkWidget *dialog;
    Status result;

    if ( !gtk_init_check(nullptr, nullptr) )
    {
        std::cout << "gtk_init_check failed to initilaize GTK+\n" ;
        return Status::STATUS_ERROR;
    }

    dialog = gtk_file_chooser_dialog_new( "Save File", nullptr,GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,"_Cancel", GTK_RESPONSE_CANCEL,"Select", GTK_RESPONSE_ACCEPT,nullptr );
    gtk_file_chooser_set_do_overwrite_confirmation( GTK_FILE_CHOOSER(dialog), TRUE );


    /* Set the default path */
    setDefaultPath(dialog, defaultPath);

    result = Status::STATUS_CANCEL;
    if ( gtk_dialog_run( GTK_DIALOG(dialog) ) == GTK_RESPONSE_ACCEPT )
    {
        pathToFile = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );

        result = Status::STATUS_OK;
    }

    waitForCleanUp();
    gtk_widget_destroy(dialog);
    waitForCleanUp();

    return result;}
