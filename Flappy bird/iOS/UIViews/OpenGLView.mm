//
//  OpenGLView.m
//  HelloOpenGL
//
//  Created by Ray Wenderlich on 5/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "OpenGLView.h"
#import "GLMatrix.hpp"
#import "GameWorld.hpp"
#import "GDirector.hpp"
#import "PostMan.hpp"

@interface OpenGLView (PrivateMethods)
- (void)setupGWorld;
- (void)setupGDirector;
@end

GameWorld* gWorld;
PostMan* postMan;

@implementation OpenGLView

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    return self;
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

-(void) setupGL
{
    [self setupLayer];
    [self setupContext];
    [self setupDepthBuffer];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
    [self setupGDirector];
    [self setupGWorld];
    [self setupPostMan];
    [self setupDisplayLink];
}

- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {   
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);        
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];    
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);    
}

- (void)setupFrameBuffer {    
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);   
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

-(void)setupGWorld
{
    gWorld = new GameWorld();
    gWorld->initLevel();
}

-(void) setupPostMan {
    postMan = new PostMan();
    postMan->addReceiver(gWorld);
}

-(void) setupGDirector
{
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    
    GDirector::getInstance()->setWinSizeInPixels(kmSizeMake(screenWidth, screenHeight));
}


- (void)render:(CADisplayLink*)displayLink {
    
    float dt = (displayLink.targetTimestamp - displayLink.timestamp);
    //float FPS = 1 / (displayLink.targetTimestamp - displayLink.timestamp);
    
    if(gWorld->end) {
        gWorld->resetLevel();
        gWorld->end = false;
    }
    gWorld->pollUpdates();
    gWorld->logic();
    gWorld->update(dt);
    gWorld->render();
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];    
}

-(void) touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)even
{
    postMan->send(0);
}
@end
