//  Created by Ali Behfarnia on 11/24.

// Message Queues
// Message Queues in C are a form of IPC that allow processes to send and receive messages

// Key Concepts:
// msgget: Creates a new message queue or accesses an existing one.
// msgsnd: Sends a message to the queue.
// msgrcv: Receives a message from the queue.
// msgctl: Performs various operations on the queue, like deletion.

// ==========================

// Example:
// In this example, we have two parts:
// 1. A parent (sender) process that sends a message to the queue.
// 2. A child (receiver) process that reads the message from the queue.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message structure
struct msg_buffer {
    long msg_type;      // This allows messages to be categorized, enabling the receiver to selectively read certain types.
    char msg_text[100]; // An array of char to hold the actual text of the message.
} message;              // message is an instance that we’ll use to send and receive messages.

int main(int argc, char* a[]) {
    key_t key;          // Key is a unique identifier (like an address) used to create/access a specific IPC resource.
                        // Role: The key itself doesn’t directly allow access to the message queue; it’s just a unique identifier used to create or locate a resource.
    
    int msgid;          // Declares a variable to store the message queue identifier.
                        // Role: It is the actual handle to the message queue that the program will use for sending, receiving, or deleting the queue.
    int id =fork();
    // Generate a unique key
    key = ftok("progfile", 88); // "progfile" is the pathname of an existing file or directory. 65 is the project identifier
    // Create a message queue and return an identifier
    msgid = msgget(key, 0666 | IPC_CREAT); // 0666: read/write permissions
    if (id == 0) {
        // ============= Message types and flags =============
        // msgtyp (here 1):
        // We can assign any positive integer as a message type.
        // These values categorize messages and allow processes to selectively receive messages.
        // Special Usage in msgrcv:
        // msgtyp > 0: Receives the first message with msg_type equal to msgtyp.
        // msgtyp = 0: Receives the first message in the queue, regardless of its type.
        // msgtyp < 0: Receives the first message with the lowest msg_type less than or equal to the |msgtyp|.
        
        // msgflg (here 0):
        // This parameter specifies the flag options for receiving messages.
        // A value of 0 means to use the default behavior, which is to wait (block) until a message of the specified type is available.
        // You can use flags like IPC_NOWAIT to return immediately if no messages are available (non-blocking).
        // Example of IPC_NOWAIT: If there's no message, the function will return -1, and errno will be set to ENOMSG to indicate that no message was found.
        msgrcv(msgid, &message, sizeof(message), message.msg_type, 0);
        printf("Received message: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL);          // Destroy the message queue
    } else {
        message.msg_type = 1; // Message type
        strcpy(message.msg_text, "Hello, this is a test message!"); // strcpy copy a message from source to destination
        msgsnd(msgid, &message, sizeof(message), 0);         // Send the message to the queue
        printf("Sent message: %s\n", message.msg_text);
    }
    return 0;
}
