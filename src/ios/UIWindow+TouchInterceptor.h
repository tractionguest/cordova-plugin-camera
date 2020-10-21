//
//  UIWindow+TouchInterceptor.h
//  CameraIdleExample
//
//  Created by Veronica Baldys on 2020-10-21.
//

#import <UIKit/UIKit.h>

static const NSNotificationName kSendEventTouchesEndedNotification = @"SendEventTouchesEndedNotification";
static const NSNotificationName kSendEventTouchesBeganNotification = @"SendEventTouchesBeganNotification";

NS_ASSUME_NONNULL_BEGIN

@interface UIWindow (TouchInterceptor)
@end

NS_ASSUME_NONNULL_END

