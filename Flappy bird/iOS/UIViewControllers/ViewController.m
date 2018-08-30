#import "ViewController.h"
#import "OpenGLView.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet OpenGLView *glView;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void) viewDidLayoutSubviews
{
    [_glView setupGL];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


@end
