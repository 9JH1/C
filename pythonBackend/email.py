from tempmail import EMail
import time

def save_to_file(filename, content):
    """ Save content to a file """
    with open(filename, 'w') as file:
        file.write(content)

def main():
    # Create a temporary email address
    email = EMail()
    email_address = email.address

    # Save the email address to a file
    save_to_file('email_address.txt', email_address)
    print(f"Email address saved to email_address.txt: {email_address}")

    # Wait for some time to allow emails to arrive
    print("Waiting for emails...")
    time.sleep(10)  # Adjust this delay as needed

    # Retrieve and save all received messages
    inbox = email.get_inbox()
    messages_content = ""

    for msg_info in inbox:
        subject = msg_info.subject
        body = msg_info.message.body
        messages_content += f"Subject: {subject}\nBody: {body}\n\n"

    save_to_file('received_emails.txt', messages_content)
    print("Received emails saved to received_emails.txt")

if __name__ == '__main__':
    main()

