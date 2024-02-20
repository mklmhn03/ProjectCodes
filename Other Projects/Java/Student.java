public class Student {
    String name;
    char grade;

    public Student(String nam, char grad) {
        name = nam;
        grade = grad;
    }

    public int compareto(Student other) {
        if (grade == other.grade) {
            if (other.name == name) return 0;
            else {
                for (int i = 0; i<name.length() && i<other.name.length(); i++) {
                    if (name.charAt(i) != other.name.charAt(i))
                        return name.charAt(i) - other.name.charAt(i);
                }
                if (name.length() < other.name.length()) return 1;
                else return -1;
            }
        }
        else return grade-other.grade;
    }
    public static void main (String args[]) {
        Student a = new Student("name", 'b');

        Student b = new Student("name", 'b');
        Student c = new Student("name", 'e');
        Student d = new Student("name", 'a');

        Student e = new Student("name", 'b');
        Student f = new Student("zname", 'b');
        Student g = new Student("aname", 'b');

        System.out.println(a.compareto(b));
        System.out.println(a.compareto(c));
        System.out.println(a.compareto(d));
        System.out.println(a.compareto(e));
        System.out.println(a.compareto(f));
        System.out.println(a.compareto(g));
    }
}