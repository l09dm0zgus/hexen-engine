//
// Created by cx9ps3 on 30.12.22.
//

#include "Application.h"
#include "../graphics/Graphics.h"
#include "../../entity/scene/SceneEntity.h"

void core::Application::run()
{
    SDL_Log("Main thread started.\n");
    double dt = 1 / 60.0;
    int currentTime = SDL_GetTicks();
    unsigned int amount = 10000;
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[amount];
  //  std::vector<TransformComponent> transforms;
    srand(currentTime); // инициализация рандома некоторым значением
    float radius = 150.0;
    float offset = 0.0f;
    for(int y = -10; y < 10; y += 1)
    {
        for(int x = -10; x < 10; x += 1)
        {
            glm::vec3 translation;
           // TransformComponent transform;
           // transform.setScale(glm::vec3(1,1,1));
            translation.x = (float)x / 1.0f + offset;
            translation.y = (float)y / 1.0f + offset;
            translation.z = 1.0f;
          //  transform.setPosition(translation);
         //   transforms.push_back(transform);
        }
    }
  //  for(int i = 0 ;i<transforms.size();i++)
   // {
   //     modelMatrices[i] = transforms[i].getTransformMatrix();
  //  }

   // SpriteInstancedComponentPool rectangle("shaders/SpriteVertexShaderInstanced.glsl", "shaders/SpriteFragmentShader.glsl", amount, modelMatrices);
   // rectangle.addTexture("images/test.jpg");
  // SpriteInstancedComponentPool pool(5);
  // SpriteInstancedComponent *sprite = pool.create("shaders/SpriteVertexShaderInstanced.glsl", "shaders/SpriteFragmentShader.glsl", amount, modelMatrices);
 //  sprite->addTexture("images/test.jpg");
    //Camera camera(window->getDisplayMode().w,window->getDisplayMode().h,45.0f);

    std::unique_ptr<ent::SceneEntity> scene = core::mem::make_unique<ent::SceneEntity>("SceneRoot",generateUUIDV4());

    while (window->isOpen())
    {
        double newTime = SDL_GetTicks();
        double frameTime = newTime - currentTime;
        currentTime = newTime;
        float deltaTime;
        window->pollEvents();
        while ( frameTime > 0.0 )
        {
            deltaTime = SDL_min( frameTime, dt );
            //update
            scene->updateTransformMatrix();
            frameTime -= deltaTime;
        }
        window->clear();
        window->swapBuffers();
    }
}

core::Application::Application()
{
    window = mem::make_unique<Window>("Battleblaze");
    SDL_Log("Main window created.\n");
}
