// Copyright (c) 2010, Erik J. Johnson
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this list
// of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice, this list of 
// conditions and the following disclaimer in the documentation and/or other materials 
// provided with the distribution.
//
// Neither the name of Erik J. Johnson nor the names of its contributors may be used 
// to endorse or promote products derived from this software without specific prior 
// written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
// OF SUCH DAMAGE.

#import <Foundation/Foundation.h>

#import "corelib/PWSfile.h"

#import "iPWSDatabaseEntryModelDelegate.h"
#import "iPWSDatabaseEntryModel.h"
#import "iPWSDatabaseModelDelegate.h"

// Class: iPWSDatabaseModel
// Description:
//  Each iPWSDatabaseModel represents a single, password-validated PasswordSafe database.  The underlying file that
//  stores the database is opened, completely re-written, and closed each time a change is made to the database
//  due to the API exposed by the underlying C model, but that is not reflected in this class.
//
@interface iPWSDatabaseModel : NSObject <iPWSDatabaseEntryModelDelegate> {
    NSMutableArray                    *entries;
    id<iPWSDatabaseModelDelegate>      delegate;
    NSString                          *fileName;
    NSString                          *friendlyName;
    NSString                          *passphrase;
    PWSfile::HeaderRecord              headerRecord;
    PWSfile                           *pwsFileHandle;
    NSError                           *lastError;
}

// Class methods
+ (NSString *)databaseVersionToString:(PWSfile::VERSION)version;
+ (BOOL)isPasswordSafeFile:(NSString *)filePath;

// Accessors 
@property (readonly) NSArray                      *entries;
@property (assign) id<iPWSDatabaseModelDelegate>   delegate;
@property (readonly) NSString                     *fileName;
@property (copy) NSString                         *friendlyName;
@property (readonly) PWSfile::VERSION              version;
@property (readonly) const PWSfile::HeaderRecord  *headerRecord;

// Initialization - if the file does not exist, a new database is created.
- (id)initNamed:(NSString *)theFriendlyName 
      fileNamed:(NSString *)theFileName
     passphrase:(NSString *)thePassphrase
       errorMsg:(NSError **)errorMsg;

// Entry modifications (passphrase required)
- (BOOL)addDatabaseEntry:(iPWSDatabaseEntryModel *)entry;
- (BOOL)removeDatabaseEntryAtIndex:(NSInteger)idx;

@end
