#import "IO.h"

@implementation IO


const char* iOSReadFile(const char* fileName)
{
    return [IO ReadFile:fileName];
}


+(const char*)ReadFile:(const char*) fileName {
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


