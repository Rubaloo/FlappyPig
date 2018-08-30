#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

struct CPPMembers;

@interface OpenGLView : UIView {
    CAEAGLLayer         * _eaglLayer;
    EAGLContext         * _context;
    GLuint              _colorRenderBuffer;
    struct CPPMembers   *_cppMembers;
}
-(void) setupGL;

@end
