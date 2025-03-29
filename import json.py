import json

def create_question(question, options, correct_option):
    return {
        "question": question,
        "options": options,
        "correct_option": correct_option
    }

def save_questions_to_file(questions, filename):
    with open(filename, 'w') as file:
        json.dump(questions, file, indent=4)

def main():
    questions = []
    while True:
        question = input("Enter the question: ")
        options = []
        for i in range(4):
            option = input(f"Enter option {i + 1}: ")
            options.append(option)
        correct_option = input("Enter the correct option: ")
        questions.append(create_question(question, options, correct_option))
        
        another = input("Do you want to add another question? (yes/no): ")
        if another.lower() != 'yes':
            break

    filename = input("Enter the filename to save the questions: ")
    save_questions_to_file(questions, filename)
    print(f"Questions saved to {filename}")

if __name__ == "__main__":
    main()