#import <Foundation/Foundation.h>
#include "IO-C-Interface.h"

@interface IO : NSObject
+(const char*)ReadFile:(const char*)fileName;
@end


