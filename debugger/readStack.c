#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};

    hSerial = CreateFile("COM7", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening serial port.\n");
        return 1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error getting serial port state.\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200; // Set the baud rate to 112500
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error setting serial port state.\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Allocate memory to store received data
    char *dataBuffer = (char *)malloc(1024 * sizeof(char)); // Adjust the size as per your requirement

    if (dataBuffer == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        CloseHandle(hSerial);
        return 1;
    }

   
    DWORD bytesRead;
    DWORD totalBytesRead = 0;
    BOOL stopReading = FALSE;

    // Read and store data from the serial port
    while (!stopReading) {
        if (ReadFile(hSerial, dataBuffer + totalBytesRead, 1024, &bytesRead, NULL)) {
            // Print the received characters
            for (DWORD i = 0; i < bytesRead; i++) {
                // Check for '!' character to stop reading
                if (dataBuffer[totalBytesRead + i] == '!') {
                    stopReading = TRUE;
                    break;
                }
                printf("%c", dataBuffer[totalBytesRead + i]);
            }

            totalBytesRead += bytesRead;
            // Resize the buffer if needed
            dataBuffer = (char *)realloc(dataBuffer, (totalBytesRead + 1024) * sizeof(char));
        } else {
            fprintf(stderr, "Error reading from serial port.\n");
            break;
        }
    }

    // Free the allocated memory when you're done with it
    free(dataBuffer);

    // Close the serial port
    CloseHandle(hSerial);

    return 0;
}