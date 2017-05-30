//
//  IO.m
//  Flapi Pig
//
//  Created by Ruben on 14/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#import "IO.h"

@implementation IO


const char* iOSreadFile(char* fileName)
{
    return [IO readFile:fileName];
}


+(const char*)readFile:(char*) fileName {
    NSString* shaderPath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:fileName] ofType:@"glsl"];
    NSError* error;
    NSString* shaderString = [NSString stringWithContentsOfFile:shaderPath
                                                       encoding:NSUTF8StringEncoding error:&error];
    if (!shaderString) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);

    }
    return [shaderString UTF8String];
}



@end


