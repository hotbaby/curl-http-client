TARGET = curl_test

all: curl_test

$(TARGET):
	gcc curl_test.c -lcurl -o $@

clear:
	rm $(TARGET) -rf
