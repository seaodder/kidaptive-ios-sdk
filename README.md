## Adaptive Learning Platform (ALP) SDK v1.1.2 Quick Start Guide
***
API version 1.1.2

## Overview
***
This library enables the integration between ALP and your iOS app.

## Requirements

- This version of the SDK is designed for iOS 6 and above.
- The sdk provides ARC support. (To use the SDK in a non-ARC project, please use the -fobjc-arc compiler flag on all the files in the Kidaptive SDK.)

## Terminology

In order to understand some of the terms used in the sdk, please read the concepts below.

##### Learner
A child who plays our games/interacts with our appisodes/consumes our content.
    
##### Learner Model
A client-side framework containing a representation of a learner’s achievements/progress in learning dimensions.
    
##### Learner ability estimates   
These are quantified estimates of a learner's proficiency at a particular skill. These estimates are adjusted as new information from relevant game play and other relevant sources enter the ALP system. These estimates also  have standard deviations to indicate how confident the system is in the estimate.
    
##### Dimension
Dimensions represent the key skills and abilities that make up Kidaptive's early learning framework.
    
##### Category
Categories represent the structured evidence that is generated when learners play learning games. Categories contain Subcategories which contain Instances (described below). This hierarchy enables games to express various relationships between elements in the game interaction (information about context) and kinds of data that will be reported as evidence of learner judgments and decisions, i.e., evidence of learner understanding. Categories can also be thought of as the aggregate of elements in a game, e.g., the category "Shape" might be used to contain a set of Instances such as "triangle", "circle", and "octagon."
    
##### Prompt
Prompts represent the smallest reportable block of activity. In many cases, this will be a learner response to a single "question." This response, then, contains the evidence (the categories and instances, or "values") of what the learner did as well as information about the context in which those actions took place. 

##### Instances
Instances represent the most specific/discrete aspect of an element in a game that a Learner could interact with and that could be reported as evidence of Learner understanding in response to some challenge. For example, an instance for the category "Color" might be "Red." 

##### Items
Items represent the smallest unit of measurement for a given Dimension or skill. Items are mapped to Prompts, from simple cases where a Prompt contains data for evaluating a single Item, to more complex cases where a single Prompt contains multiple pieces of data which can be used to evaluate multiple items. Data in Prompt responses are mapped to Items and evaluated, turning the Prompt response into one or more Item Attempts.
    
##### Item Attempts
Item attempts are the evaluated outcomes of learner interactions. They are typically binary, successful or not, although they can represent other types of outcomes. Because Items are linked to particular skills (Dimensions), Item attempts are also linked to particular skills. Item attempts are the inputs to scoring processes like IRT analysis.

##### Level
A difficulty level is a configuration of Difficulty Factors that generates a set of Challenges that are comparable in difficulty.

##### Client IRT Control
Often learners are given multiple chances to solve a given puzzle or otherwise respond to a single challenge, but the second or subsequent response shouldn't be scored and analyzed in the IRT process in the same way as the initial attempt. Consequently, games can and should indicate when a particular Prompt response should or shouldn't be used to contribute to a Learner ability estimate by appropriately setting the SKIP_ITEM_IRT/SKIP_LEARNER_IRT flags according to whether the Learner's response is an initial or subsequent effort on a given challenge.  
    
## Getting Started

This document covers getting set up with the Kidaptive SDK, some quick examples, and some discussion of the primary classes. 

### Installation
Getting started is easy. Just install the library using [Cocoapods](http://cocoapods.org/).

##### Installing Podfile
```ruby
pod 'Kidaptive', :git => 'git@github.com:Kidapt/kidaptive-sdk-ios.git', :tag => '1.1.1'
```
### Using the Kidaptive SDK

##### Importing Kidaptive Library

``` objective-c
#import <Kidaptive.h>
```
### Authenticate User

When the session starts up, if it's not already authenticated, you'll need to authenticate the user using the following method. 
``` objective-c
[[Kidaptive alloc] initWithUsername:username password:password delegate:self];
```
**_Parameters_**

- username (NSString): User email address
- password (NSString): User password
- delegate (KidaptiveDelegate): The delegating object KidaptiveDelegate 

**_Response_**

KidaptiveDelegate will implement the following responses:
- kidaptiveDidNotLogin : sdk is unable to login using the username and password
``` objective-c
- (void)kidaptDidNotLogin:(Kidaptive*) kidaptive withError:(NSError*)error;
```
- kidaptiveDidLogin : sdk was able to login successfully, Kidaptive instance is returned
``` objective-c
-(void)kidaptiveDidLogin:(Kidaptive *)kidaptive;
```
- kidaptiveDidLogout : sdk has logged out
``` objective-c
-(void)kidaptiveDidLogout;
```

### Create User
You can create a new kidaptive user. 
``` objective-c
KidaptiveUser* kidaptiveUser = [[KidaptiveUser alloc] init];
[kidaptiveUser name:@"John Smith"];
[kidaptiveUser email:@"js@mail.com"];
[kidaptiveUser password:@"xxxxxxxxx"];
[kidaptive createUser:kidaptiveUser failure:^(NSError *error) {
                            failure:^(NSError *error) {
                                // failure... show error notification, etc
                                NSLog(@"error %@", error);                                                       } else {
                              // user creation succeeded :)    
                            }];
```

**_Parameters_**

- kidaptiveUser (kidaptiveUser): kidaptive user

**_Response_**

- error (NSError) : error if user creation fails 

### Retrieve User
You can retrieve an existing kidaptive user once you've signed in. 
``` objective-c
[kidaptive getUserWithSuccess:^(KidaptiveUser *kidaptiveUser) {
                                // success... 
                                NSLog(@"kidaptiveUser: %@", kidaptiveUser);
                            }
                            failure:^(NSError *error) {
                                // failure... user not found or not authenticated
                                NSLog(@"error %@", error);                                            
                            }];
```
**_Response_**

- kidaptiveUser (KidaptiveUser) : kidaptive user
- error (NSError) : error if user creation fails 

### Update User
You can update an existing kidaptive user. 
``` objective-c
KidaptiveUser* kidaptiveUser = (See Retrieve User)
[kidaptiveUser name:@"Jim Butler"];
[kidaptive updateUser:kidaptiveUser failure:^(NSError *error) {
                            failure:^(NSError *error) {
                                // failure... show error notification, etc
                                NSLog(@"error %@", error);                                                       } else {
                              // user update succeeded :)    
                            }];
```

**_Parameters_**

- kidaptiveUser (KidaptiveUser):  Kidaptive User Object

**_Response_**

- error (NSError) : error if user update fails 


### Create Learner
You can create a new kidaptive learner. 
``` objective-c
KidaptiveLearner* kidaptiveLearner = [[KidaptiveLearner alloc] init];
[kidaptiveLearner name:@"Talor Myers"];
[kidaptiveLearner gender:@"female"];
NSDateComponents *date = [[NSDateComponents alloc] init];
[components setYear:2010];
[components setMonth:3];
[components setDay:17];
[kidaptiveLearner birthday:date];
[kidaptive createLearner:kidaptiveLearner failure:^(NSError *error) {
                            failure:^(NSError *error) {
                                // failure... show error notification, etc
                                NSLog(@"error %@", error);                                                       } else {
                              // learner creation succeeded :)    
                            }];
```

**_Parameters_**

- kidaptiveLearner (kidaptiveLearner) : kidaptive learner

**_Response_**

- error (NSError) : error if learner creation fails 

### List Learners
You can retrieve learners once you've signed in. 
``` objective-c
[kidaptive listLearnerWithSuccess:^(NSArray *kidaptivelearners) {
                                // success... 
                                NSLog(@"kidaptivelearners: %@", kidaptivelearners);
                            }
                            failure:^(NSError *error) {
                                // failure... learners not found
                                NSLog(@"error %@", error);                                            
                            }];
```
**_Response_**

- kidaptivelearners (NSArray) :  list of kidpative learners (KidaptiveLearner)
- error (NSError) : error if user creation fails 

### Update Learner
You can update an existing kidaptive learner. 
``` objective-c
KidaptiveLearner* kidaptiveLearner = (See Retrieve Learner)
[kidaptiveLearner name:@"Paul McCartney"];
[kidaptive updateLearner:kidaptiveLearner failure:^(NSError *error) {
                            failure:^(NSError *error) {
                                // failure... show error notification, etc
                                NSLog(@"error %@", error);                                                       } else {
                              // learner update succeeded :)    
                            }];
```

**_Parameters_**

- kidaptiveLearner (kidaptiveLearner):  Kidaptive Learner Object

**_Response_**

- error (NSError) : error if user update fails 


### Delete Learner
You can delete an existing kidaptive learner. 
``` objective-c
KidaptiveLearner* kidaptiveLearner = (See Retrieve Learner)
[kidaptiveLearner name:@"Paul McCartney"];
[kidaptive deleteLearner:kidaptiveLearner failure:^(NSError *error) {
                            failure:^(NSError *error) {
                                // failure... show error notification, etc
                                NSLog(@"error %@", error);                                                       } else {
                              // learner delete succeeded :)    
                            }];
```

**_Parameters_**

- kidaptiveLearner (kidaptiveLearner):  Kidaptive Learner Object

**_Response_**

- error (NSError) : error if learner delete fails 

### Retrieve Learner Abilities
``` objective-c
KidaptiveLearner* kidaptiveLearner = (See Retrieve Learner)
NSArray *categories = @[@123, @456];
NSDictionary* abilities = [kidaptive getAbilitiesForLearner: learner withCategories:categories];
```

**_Parameters_**
- learner (KidaptiveLearner): current active learner
- categories (NSArray): list of categories 

**_Response_**
- Learner Abilities (NSDictionary): learner abitilies for categories

    
### Reporting Learner Evidence

``` objective-c	
KidaptiveLearner* kidaptiveLearner = (See Retrieve Learner)
KidaptiveEvidence* evidence = [[KidaptiveEvidence alloc] init];
[evidence prompt:@2222];
[evidence source:@3333];
[evidence level:@1];
[evidence skipIRT:@"true"];
KidaptiveAnswer* answer = [[KidaptiveAnswer alloc] init]; 
[answer category:@4441 instance:5551];
[answer category:@4442 instance:5552];
[answer category:@4443 instance:5553];
[evidence answer:answer];
KidaptiveAttempts* attempts = [[KidaptiveAttempt alloc] init];
[attempts addAttemptForDimension:@7771 item:@8881 outcome@"true"];
[attempts addAttemptForDimension:@7772 item:@8882 outcome@"false"];
[attempts addAttemptForDimension:@7773 item:@8883 outcome@"true"];

[kidaptive reportEvidenceforLearner:kidaptiveLearner evidence:evidence];
```

**_Parameters_**
- learner (KidaptiveLearner): Current Active Learner
- evidence (KidaptiveEvidence): 

**_Response_**	
- void
