//
//  Renderer.hpp
//  Flapi Pig
//
//  Created by Ruben on 17/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
//#include "Shader.hpp"


class Renderer {
    
public:
    void setupRenderContext();
    void render();
   private:
    //Shader* pipeline;
};

#endif /* Renderer_hpp */
