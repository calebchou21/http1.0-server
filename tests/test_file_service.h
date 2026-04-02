#ifndef TEST_FILE_SERVICE_H
#define TEST_FILE_SERVICE_H

int runFileServiceTests();

int getRequestWithUnsafePath();
int getRequestWithNonExistantFile();
int getRequestNotModified();
int getRequestOk();

int headRequestWithUnsafePath();
int headRequestWithNonExistantFile();
int headRequestNotModified();
int headRequestOk();

#endif
