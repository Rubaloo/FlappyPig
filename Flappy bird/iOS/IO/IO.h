#import <Foundation/Foundation.h>
#include "IO-C-Interface.h"
#include <string>

@interface IO : NSObject
+(const char*)ReadFile:(const std::string&)fileName;
@end


