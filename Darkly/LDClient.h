//
//  Copyright © 2015 Catamorphic Co. All rights reserved.
//

#import "LDConfig.h"
#import "LDUserBuilder.h"

@class LDConfig;
@class LDUserBuilder;


@protocol ClientDelegate
@required
@property (nonatomic, weak) id<ClientDelegate> delegate;
-(void)userDidUpdate;
@end

@interface LDClient : NSObject

@property(nonatomic, strong, readonly) LDUser *user;
@property(nonatomic, strong, readonly) LDConfig *ldConfig;
@property (nonatomic, assign) id delegate;

+ (id)sharedInstance;

/**
 * Start the client with a valid configuration and user.
 *
 * @param inputConfigBuilder    Desired configuration for the client
 * @param inputUserBuilder  Desired user for the client
 * @return whether the client was able to be started
 */
- (BOOL)start:(LDConfigBuilder *)inputConfigBuilder userBuilder:(LDUserBuilder *)inputUserBuilder;
/**
 * Retrieve a feature flag value. If the configuration for this feature
 * flag is retrieved from the server that value is returned, otherwise
 * the defaultValue is returned.
 *
 * @param featureName   Name of feature flag
 * @param default   Default value for feature flag
 * @return the feature flag value
 */
- (BOOL)toggle:(NSString *)featureName default:(BOOL)defaultValue;
/**
 * Track a custom event.
 *
 * @param eventName Name of the custom event
 * @param data  Data to be attached to custom event
 * @return whether the event was successfully recorded
 */
- (BOOL)track:(NSString *)eventName data:(NSDictionary *)dataDictionary;
/**
 * Update the user after the client has started. This will override
 * user information passed in via the start method.
 *
 * @param builder   Desired user for the client
 * @return whether the user was successfully updated
 */
- (BOOL)updateUser:(LDUserBuilder *)builder;
/**
 * Retrieve the current user.
 *
 * @return the current user.
 */
- (LDUserBuilder *)currentUserBuilder;
/**
 * Set the client to offline mode. No events will be synced to server.
 *
 * @return whether offline mode was successfully updated.
 */
- (BOOL)offline;
/**
 * Set the client to online mode. Events will be synced to server. (Default)
 *
 * @return whether online mode was successfully updated.
 */
- (BOOL)online;
/**
 * Sync all events to the server. Events are synced to the server on a
 * regular basis, however this will force all stored events from the client
 * to be synced immediately to the server.
 *
 * @return whether events were able to be flushed.
 */
- (BOOL)flush;
/**
 * Stop the client.
 *
 * @return whether the client was able to be stopped.
 */
- (BOOL)stopClient;

@end
