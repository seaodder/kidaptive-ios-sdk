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


/**
 * Retrieve active user 
 * 
 */
- (void)getUserWithSuccess:^(KidaptiveUser *kidaptiveUser)
                   failure:(void(^)(NSError *error))failure;

/**
 * Update active user 
 * @param KidaptiveUser  Kidaptive User object
 * 
 */
- (void)updateUser:(KidaptiveUser*)user
        failure:(void(^)(NSError *error))failure;

/**
 * Creates a new learner  
 * @param KidaptiveLearner  Kidaptive User object
 */
- (void)createLearner:^(kidaptiveLearner *kidaptiveLearner)
              failure:(void(^)(NSError *error))failure;


/**
 * Retrieve learners  
 * @param KidaptiveLearner  Kidaptive User object
 */
- (void)listLearnerWithSuccess:^(NSArray *kidaptivelearners)
                       failure:(void(^)(NSError *error))failure;

/**
 * Update learner  
 * @param KidaptiveLearner  Kidaptive User object
 */
- (void)updateLearner:(kidaptiveLearner*) kidaptiveLearner
              failure:(void(^)(NSError *error))failure;

/**
 * Delete learner  
 * @param KidaptiveLearner  Kidaptive User object
 */
- (void)deleteLearner:(kidaptiveLearner*) kidaptiveLearner
              failure:(void(^)(NSError *error))failure;

/**
 * Retrieve Abilities for learner  
 * @param KidaptiveLearner  Kidaptive User object
 */
- (NSDictionary* ) getAbilitiesForLearner:(KidaptiveLearner*) kidaptiveLearner withCategories:(NSArray*) categories;


/**
 * Report Evidence for learner 
 * @param KidaptiveLearner  Kidaptive User object
 */
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
