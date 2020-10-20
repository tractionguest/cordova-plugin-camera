/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLLocationManager.h>
#import <Cordova/CDVPlugin.h>

enum CDVDestinationType {
    DestinationTypeDataUrl = 0,
    DestinationTypeFileUri
};
typedef NSUInteger CDVDestinationType;

enum CDVEncodingType {
    EncodingTypeJPEG = 0,
    EncodingTypePNG
};
typedef NSUInteger CDVEncodingType;

enum CDVMediaType {
    MediaTypePicture = 0,
    MediaTypeVideo,
    MediaTypeAll
};
typedef NSUInteger CDVMediaType;

@interface CDVPictureOptions : NSObject

@property (strong) NSNumber* quality;
@property (assign) CDVDestinationType destinationType;
@property (assign) UIImagePickerControllerSourceType sourceType;
@property (assign) CGSize targetSize;
@property (assign) CDVEncodingType encodingType;
@property (assign) CDVMediaType mediaType;
@property (assign) BOOL allowsEditing;
@property (assign) BOOL correctOrientation;
@property (assign) BOOL saveToPhotoAlbum;
@property (strong) NSDictionary* popoverOptions;
@property (assign) UIImagePickerControllerCameraDevice cameraDirection;
@property (strong) NSNumber* idleTimeout;

@property (assign) BOOL popoverSupported;
@property (assign) BOOL usesGeolocation;
@property (assign) BOOL cropToSize;

+ (instancetype) createFromTakePictureArguments:(CDVInvokedUrlCommand*)command;

@end

@interface CDVCameraPicker : UIImagePickerController

@property (strong) CDVPictureOptions* pictureOptions;

@property (copy)   NSString* callbackId;
@property (copy)   NSString* postUrl;
@property (strong) UIPopoverController* pickerPopoverController;
@property (assign) BOOL cropToSize;
@property (strong) UIView* webView;

// This will get called after the timeout has completed when touch events stop firing
@property (nonatomic, copy, nullable) void (^idleTimeoutCallback)(void);
//@property (strong) NSTimer* _Nullable idleTimer;

- (void)cancelTimer;
// Restart the idle timer by cancelling previous timer and creating a new one
- (void)restartTimer;

+ (instancetype) createFromPictureOptions:(CDVPictureOptions*)options;

- (void)encodeWithCoder:(nonnull NSCoder *)coder;

- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection;

- (void)preferredContentSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container;

- (CGSize)sizeForChildContentContainer:(nonnull id<UIContentContainer>)container withParentContainerSize:(CGSize)parentSize;

- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container;

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator;

- (void)willTransitionToTraitCollection:(nonnull UITraitCollection *)newCollection withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator;

- (void)didUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context withAnimationCoordinator:(nonnull UIFocusAnimationCoordinator *)coordinator;

- (void)setNeedsFocusUpdate;

- (BOOL)shouldUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context;

- (void)updateFocusIfNeeded;

@end

// ======================================================================= //

@interface CDVCamera : CDVPlugin <UIImagePickerControllerDelegate,
                       UINavigationControllerDelegate,
                       UIPopoverControllerDelegate,
                       CLLocationManagerDelegate>
{
}

@property (strong) CDVCameraPicker* pickerController;
@property (strong) NSMutableDictionary *metadata;
@property (strong, nonatomic) CLLocationManager *locationManager;
@property (strong) NSData* data;
//

/*
 * getPicture
 *
 * arguments:
 *	1: this is the javascript function that will be called with the results, the first parameter passed to the
 *		javascript function is the picture as a Base64 encoded string
 *  2: this is the javascript function to be called if there was an error
 * options:
 *	quality: integer between 1 and 100
 */
- (void)takePicture:(CDVInvokedUrlCommand*)command;
- (void)cleanup:(CDVInvokedUrlCommand*)command;
- (void)repositionPopover:(CDVInvokedUrlCommand*)command;

- (void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary*)info;
- (void)imagePickerController:(UIImagePickerController*)picker didFinishPickingImage:(UIImage*)image editingInfo:(NSDictionary*)editingInfo;

- (void)imagePickerControllerDidCancel:(UIImagePickerController*)picker;
- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated;

- (void)locationManager:(CLLocationManager*)manager didUpdateToLocation:(CLLocation*)newLocation fromLocation:(CLLocation*)oldLocation;
- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error;

@end

//@interface IdleTimer: NSObject
//
//+ (void)setup:(void (^_Nonnull)(void))idleCompletionBlock timeInterval:(NSTimeInterval)interval;
//// invalidate and initialize timer
//+ (void)restart;
//// invalidates timer
//+ (void)reset;

//@property (nonatomic, strong) NSTimer* _Nullable idleTimer;

//@property (nonatomic, copy, nonnull, readonly) void (^idleCompletionBlock)(void);



NS_ASSUME_NONNULL_BEGIN

@interface UIButton (TouchEventNotifications)
@end

NS_ASSUME_NONNULL_END

//NS_ASSUME_NONNULL_BEGIN
//
//@interface UIView (IdleTimerTrigger)
//@end
//
//NS_ASSUME_NONNULL_END
