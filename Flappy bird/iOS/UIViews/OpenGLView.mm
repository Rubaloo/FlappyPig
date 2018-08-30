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
}


+ (Class)layerClass {
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

- (void)setupFrameBuffer {    
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);   
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
}

-(void)setupGWorld
{
    _cppMembers->gWorld = new GameWorld();
    _cppMembers->gWorld->initLevel();
}

-(void) setupPostMan {
    _cppMembers->postman = new PostMan();
    _cppMembers->postman->addReceiver(_cppMembers->gWorld);
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
    
    if(_cppMembers->gWorld->isLevelFinished()) {
        _cppMembers->gWorld->resetLevel();
        _cppMembers->gWorld->setLevelFinished(false);
    } else{
        _cppMembers->gWorld->pollUpdates();
        _cppMembers->gWorld->logic();
        _cppMembers->gWorld->update(dt);
        _cppMembers->gWorld->render();
    }
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];    
}

-(void) touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)even
{
    _cppMembers->postman->send(0);
}
@end
