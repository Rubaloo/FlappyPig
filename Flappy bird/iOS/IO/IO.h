//
//  IO.h
//  Flapi Pig
//
//  Created by Ruben on 14/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "IO-C-Interface.h"

@interface IO : NSObject
+(const char*)readFile:(char*)fileName;
@end


