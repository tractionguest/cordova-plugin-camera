//
//  UIWindow+TouchInterceptor.m
//  CameraIdleExample
//
//  Created by Veronica Baldys on 2020-10-21.
//

#import <objc/runtime.h>
#import "UIWindow+TouchInterceptor.h"

@implementation UIWindow (TouchInterceptor)

- (void)xxx_sendEvent:(UIEvent *)event {
    [self xxx_sendEvent:event];
    
    if (event.type == UIEventTypeTouches) {
        
        NSSet<UITouch *> *touches = [event allTouches];
        UITouch *lastTouch = touches.allObjects.lastObject;
                
        switch (lastTouch.phase) {
            case UITouchPhaseBegan:
                [[NSNotificationCenter defaultCenter] postNotificationName:kSendEventTouchesBeganNotification
                                                                    object:[[lastTouch view] class]];
                break;
            case UITouchPhaseMoved:
                break;
            case UITouchPhaseCancelled:
                break;
            case UITouchPhaseEnded:
                if ([NSStringFromClass([lastTouch.view class]) isEqualToString:@"CUShutterButton"] || [NSStringFromClass([lastTouch.view class]) isEqualToString:@"PLTileContainerView"]) break;
                
                [[NSNotificationCenter defaultCenter] postNotificationName:kSendEventTouchesEndedNotification
                                                                    object:[[lastTouch view] class]];
                break;
            default:
                break;
        }
    }
}

+ (void)load {
    static dispatch_once_t once_token;
    dispatch_once(&once_token,  ^{
        SEL sendEventSelector = @selector(sendEvent:);
        SEL sendEventInterceptor = @selector(xxx_sendEvent:);
        
        Method originalMethod1 = class_getInstanceMethod(self, sendEventSelector);
        Method extendedMethod1 = class_getInstanceMethod(self, sendEventInterceptor);
        method_exchangeImplementations(originalMethod1, extendedMethod1);
        
    });
}

@end
