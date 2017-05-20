//
//  ViewController.m
//  Flappy bird
//
//  Created by Ruben on 20/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#import "ViewController.h"
#import "OpenGLView.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet OpenGLView *glView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
  
}

-(void) viewDidLayoutSubviews
{
  [_glView setupGL];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
