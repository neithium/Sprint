class Bank:
    def __init__(self, initialBalance=0):
        self.__acc_id = 0
        self.__balance = initialBalance

    def setBalance(self, balance):
        self.__balance = balance

    def setAccId(self, acc_id):
        self.__acc_id = acc_id

    def deposit(self, money):
        if money > 0:
            self.__balance += money

    def withdraw(self, money):
        if money <= 0:
            return

        if money > self.__balance:
            print("Insufficient balance")
            return

        self.__balance -= money

    def getBalance(self):
        print("Current balance:", self.__balance)

    def getAccId(self):
        print("Account ID:", self.__acc_id)


class Person:
    def __init__(self, age=0, name=""):
        self.__age = age
        self.__name = name

    def introduce(self):
        raise NotImplementedError


class Student(Person):
    def __init__(self, rollno=0, grade=None, age=0, name=""):
        super().__init__(age, name)

        self.__rollno = rollno
        self.__grade = grade

    def introduce(self):
        print("I am a student")

    def set_grade(self, grade):
        self.__grade = grade

    def get_grade(self):
        print("The grade of student is", self.__grade)


class Teacher(Person, Bank):
    def __init__(self, age, name, empId, salary):
        Person.__init__(self, age, name)
        Bank.__init__(self)

        self.__empId = empId
        self.__salary = salary

    def updateStudentGrade(self, student, grade):
        student.set_grade(grade)
        student.get_grade()

    def introduce(self):
        print("I am a teacher")


# ---------------- MAIN ----------------

b = Bank()

b.setAccId(23)
b.setBalance(3500)

b.deposit(34323)
b.withdraw(3343)

b.getBalance()
b.getAccId()


t = Teacher(25, "ARUN", 83, 40000.0)

s = Student(23, 'A', 16, "VARUN")

s.introduce()

t.deposit(3400)
t.setAccId(43)

t.updateStudentGrade(s, 'C')