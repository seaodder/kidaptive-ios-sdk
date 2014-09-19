//
//  Kidaptive.m
//  Kidaptive
//
//  Created by Marcelo Oliveira on 4/26/14.
//  Copyright (c) 2014 Marcelo Oliveira. All rights reserved.
//

#import <Foundation/Foundation.h>


@class Kidaptive;
@protocol KidaptiveDelegate;


@interface Kidaptive : NSObject


@property(nonatomic, weak) id<KidaptiveDelegate> kidaptiveDelegate;


/**
 * Initializes an instance of Kidaptive with the user credentials provided. 
 * @param username  The user email address
 * @param password  The user password
 * @param delegate  The delegate of the Kidaptive instance
 */
 
-(Kidaptive *)initWithUsername:(NSString*)username
                     password:(NSArray*)password
                     delegate:(id<KidaptiveDelegate>)delegate;


/**
 * Creates a new user an instance of Kidaptive with the user credentials provided. 
 * @param KidaptiveUser  Kidaptive User object
 * @param password  The user password
 * @param delegate  The delegate of the Kidaptive instance
 */
 
- (void)createUser:(KidaptiveUser*)user
           failure:(void(^)(NSError *error))failure;


- (void)getUserWithSuccess:^(KidaptiveUser *kidaptiveUser)
                   failure:(void(^)(NSError *error))failure;

- (void)updateUser:^(KidaptiveUser *kidaptiveUser)
        failure:(void(^)(NSError *error))failure;

- (void)createLearner:^(kidaptiveLearner *kidaptiveLearner)
              failure:(void(^)(NSError *error))failure;


- (void)listLearnerWithSuccess:^(NSArray *kidaptivelearners)
                       failure:(void(^)(NSError *error))failure;

- (void)updateLearner:(kidaptiveLearner*) kidaptiveLearner
              failure:(void(^)(NSError *error))failure;

- (void)deleteLearner:(kidaptiveLearner*) kidaptiveLearner
              failure:(void(^)(NSError *error))failure;

- (NSDictionary* ) getAbilitiesForLearner:(KidaptiveLearner*) kidaptiveLearner withCategories:(NSArray*) categories;



- (void) reportEvidenceforLearner:(KidaptiveLearner*) kidaptiveLearner evidence:(KidaptiveEvidence)evidence;


@end



@protocol KidaptiveDelegate <NSObject>


/**
 * This delegate method is invoked when item difficulties are updated on
 * the local device
 */
- (void)kidaptive:(Kidaptive*)kidaptive kidaptDidNotLogin:(Kidaptive*)kidaptive withError:(NSError*)error;

- (void)kidaptive:(Kidaptive*)kidaptive kidaptiveDidLogin:(Kidaptive*)kidaptive;

- (void)kidaptive:(Kidaptive*)kidaptive kidaptiveDidLogout;

@end
