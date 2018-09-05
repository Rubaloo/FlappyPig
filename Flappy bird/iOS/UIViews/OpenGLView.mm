#import "OpenGLView.h"
#import "GLMatrix.hpp"
#import "GameWorld.hpp"
#import "GDirector.hpp"
#import "PostMan.hpp"

struct CPPMembers
{
    GameWorld*  gWorld;
    PostMan*    postman;
};


@interface OpenGLView (PrivateMethods)
    - (void)setupGWorld;
    - (void)setupGDirector;
    - (PostMan*&) GetPostman;
    - (GameWorld*&) GetGameWorld;
@end




@implementation OpenGLView

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if(self)
    {
        _cppMembers = new CPPMembers;
    }
    return self;
}

- (void)dealloc
{
    delete _cppMembers;
    
    glDeleteBuffers(1, &_colorRenderBuffer);
    glDeleteBuffers(1, &_framebuffer);
}


+ (Class)layerClass
{
    return [CAEAGLLayer class];
}


-(void) setupGL
{
    [self setupLayer];
    [self setupContext];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
    [self setupGDirector];
    [self setupGWorld];
    [self setupPostMan];
    [self setupDisplayLink];
}

- (void)setupLayer
{
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext
{
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

- (void)setupRenderBuffer
{
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);        
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];    
}

- (void)setupFrameBuffer
{
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
}

-(void)setupGWorld
{
    [self GetGameWorld] = new GameWorld();
    [self GetGameWorld]->InitLevel();
}

-(void) setupPostMan
{
    [self GetPostman] = new PostMan();
    [self GetPostman]->AddReceiver([self GetGameWorld]);
}

-(void) setupGDirector
{
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    
    GDirector::getInstance()->SetWinSizeInPixels(kmSizeMake(screenWidth, screenHeight));
}

- (PostMan*&) GetPostman
{
    return _cppMembers->postman;
}

- (GameWorld*&) GetGameWorld
{
    return _cppMembers->gWorld;
}


- (void)render:(CADisplayLink*)displayLink
{
    float dt = (displayLink.targetTimestamp - displayLink.timestamp);
    //float FPS = 1 / (displayLink.targetTimestamp - displayLink.timestamp);
    
    GameWorld* gWorld = [self GetGameWorld];
    
    if(gWorld->IsLevelFinished()) {
        gWorld->ResetLevel();
        gWorld->SetLevelFinished(false);
    } else{
        gWorld->PollUpdates();
        gWorld->Logic();
        gWorld->Update(dt);
        gWorld->Render();
    }
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink
{
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];    
}

-(void) touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)even
{
    [self GetPostman]->Send(0);
}

@end
