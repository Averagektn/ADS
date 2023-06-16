import java.util.*;

public class Main {

    static final String SPACE = "    ";
    static final String RED   = "\u001b[31m";
    static final String RESET = "\u001b[0m";

    static HashMap <String, Term> getSubTerm(HashMap <String, Term> terms, String word){
        return terms.get(word).getChildren();
    }

    static HashMap <String, Term> getSubSubTerm(HashMap <String, Term> terms, String word, String sub_word){
        return terms.get(word).getChildren().get(sub_word).getChildren();
    }

    static void alphabetSort(HashMap<String, Term> terms, String space){
        String[] words = terms.keySet().toArray(new String[0]);
        Arrays.sort(words);
        for(int i = 0; i < terms.size(); i++){
            System.out.print(space + words[i] + "  ");
            System.out.println(terms.get(words[i]).getPage());
            alphabetSort(terms.get(words[i]).getChildren(), space + SPACE);
        }
    }

    static void pageSort(HashMap<String, Term> terms, String space){
        String[] words = terms.keySet().toArray(new String[0]);
        Arrays.sort(words, (o1, o2) -> {
            int page1 = (int)terms.get(o1).getPage().toArray()[0];
            int page2 = (int)terms.get(o2).getPage().toArray()[0];
            return Integer.compare(page1, page2);
        });
        for(int i = 0; i < terms.size(); i++){
            System.out.print(space + words[i] + "  ");
            System.out.println(terms.get(words[i]).getPage());
            pageSort(terms.get(words[i]).getChildren(), space + SPACE);
        }
    }

    static void findSubTerm(String name, HashMap <String, Term> terms){
        System.out.print(name + "  ");
        System.out.println(terms.get(name).getPage());
        if (getSubTerm(terms, name).isEmpty())
            System.out.println(RED + "No sub-terms found" + RESET);
        else
            showTerms(getSubTerm(terms, name), SPACE);
    }

    static void findTerm(String name, HashMap <String, Term> terms){
        String[] words = terms.keySet().toArray(new String[0]);

        for(int i = 0; i < terms.size(); i++){
            if (getSubTerm(terms, words[i]).containsKey(name)) {
                System.out.print(words[i] + "  ");
                System.out.println(terms.get(words[i]).getPage());
                showTerms(getSubTerm(terms, words[i]), SPACE);
            }
        }
    }

    static void showTerms(HashMap <String, Term> terms, String space){
        String[] words = terms.keySet().toArray(new String[0]);

        for (int i = 0; i < terms.size(); i++){
            System.out.print(space + words[i] + "  ");
            System.out.println(terms.get(words[i]).getPage());
            showTerms(getSubTerm(terms, words[i]), space + SPACE);
        }
    }

    static void deleteTerm(String name, HashMap <String, Term> terms){
        if (terms.containsKey(name))
            terms.remove(name);
        else
            System.out.println(RED + "This word does not exist" + RESET);
    }

    static void addTerm(String name, HashMap<String, Term> terms){
        if (terms.containsKey(name))
            System.out.println(RED + "This word is already exists" + RESET);
        else {
            Term term = new Term(name, addPage());
            terms.put(name, term);
        }
    }

    static HashSet<Integer> addPage(){
        String answer;
        HashSet <Integer> pages = new HashSet<>();
        boolean isInputPage = true;
        Scanner scanner = new Scanner(System.in);

        while (isInputPage) {
            System.out.println("Enter page: ");
            int add_int = scanner.nextInt();
            pages.add(add_int);
            System.out.println("Add another page? (y/n)");
            answer = scanner.next();
            if (Objects.equals(answer, "n"))
                isInputPage = false;
        }
        return pages;
    }

    static void changePage(Term term){
        term.setPage(addPage());
    }

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        HashMap <String, Term> terms = new HashMap<>();
        boolean isPlaying = true;

        while (isPlaying) {
            System.out.println("""
                    Choose option:
                    (0) exit
                    (1) add
                    (2) show
                    (3) delete
                    (4) find
                    (5) change page
                    (6) sort""");
            int option = scanner.nextInt();
            switch (option) {
                case 0 -> isPlaying = false;
                case 1 -> {
                    System.out.println("""
                            Choose option:
                            (1) add term
                            (2) add sub-term
                            (3) add sub-sub-term""");
                    int decision = scanner.nextInt();
                    switch (decision) {
                        case 1 -> {
                            System.out.println("Enter name: ");
                            String name = scanner.next();
                            addTerm(name, terms);
                        }

                        case 2 -> {
                            System.out.println("Enter term");
                            String name = scanner.next();
                            System.out.println("Enter sub-term: ");
                            String sub_name = scanner.next();
                            if (terms.containsKey(name))
                                addTerm(sub_name, getSubTerm(terms, name));
                            else
                                System.out.println(RED + "There is no such term" + RESET);
                        }
                        case 3 -> {
                            String[] words = terms.keySet().toArray(new String[0]);
                            System.out.println("Enter sub-term");
                            String sub_name = scanner.next();
                            System.out.println("Enter sub-sub-term: ");
                            String name = scanner.next();
                            for (int i = 0; i < terms.size(); i++)
                                if (getSubTerm(terms, words[i]).containsKey(sub_name))
                                    addTerm(name, getSubSubTerm(terms, words[i], sub_name));

                        }
                    }
                }

                case 2 -> showTerms(terms, "");

                case 3 -> {
                    System.out.println("""
                            Choose option:
                            (1) delete term
                            (2) delete sub-term
                            (3) delete sub-sub-term""");
                    int decision = scanner.nextInt();

                    switch (decision) {
                        case 1 -> {
                            System.out.println("Enter term");
                            String name = scanner.next();
                            deleteTerm(name, terms);
                        }

                        case 2 -> {
                            System.out.println("Enter term");
                            String name = scanner.next();
                            System.out.println("Enter sub-term");
                            String sub_name = scanner.next();
                            deleteTerm(sub_name, getSubTerm(terms, name));
                        }

                        case 3 -> {
                            System.out.println("Enter term");
                            String name = scanner.next();
                            System.out.println("Enter sub-term");
                            String sub_name = scanner.next();
                            System.out.println("Enter sub-sub-term");
                            String sub_sub_name = scanner.next();
                            deleteTerm(sub_sub_name, getSubSubTerm(terms, name, sub_name));
                            }
                        }

                    }

                case 4 -> {
                    System.out.println("""
                            Choose option:
                            (1) find term
                            (2) find sub-term""");
                    int decision = scanner.nextInt();
                    switch (decision) {

                        case 1 -> {
                            System.out.println("Enter sub-term's name");
                            String name = scanner.next();
                            findTerm(name, terms);
                        }

                        case 2 -> {
                            System.out.println("Enter term's name");
                            String name = scanner.next();
                            findSubTerm(name, terms);
                        }
                    }
                }

                case 5 -> {
                    System.out.println("""
                            Choose option:
                            (1) change term's page
                            (2) change sub-term's page
                            (3) change sub-sub-terms page""");
                    int decision = scanner.nextInt();

                    switch (decision) {
                        case 1 -> {
                            System.out.println("Enter term");
                            String name = scanner.next();
                            changePage(terms.get(name));
                        }

                        case 2 -> {
                            String[] words = terms.keySet().toArray(new String[0]);
                            System.out.println("Enter sub-term");
                            String sub_name = scanner.next();
                            Term term = new Term(sub_name, addPage());
                            for (int i = 0; i < terms.size(); i++)
                                if (getSubTerm(terms, words[i]).containsKey(sub_name))
                                    getSubTerm(terms, words[i]).put(sub_name, term);
                        }

                        case 3 -> {
                            String[] words = terms.keySet().toArray(new String[0]);
                            System.out.println("Enter sub-sub-term");
                            String sub_sub_name = scanner.next();
                            Term term = new Term(sub_sub_name, addPage());
                            for (int i = 0; i < terms.size(); i++)
                                if (getSubSubTerm(terms, words[i], sub_sub_name).containsKey(sub_sub_name))
                                    getSubSubTerm(terms, words[i], sub_sub_name).put(sub_sub_name, term);
                        }
                    }
                }

                case 6 -> {
                    System.out.println("""
                            Choose option:
                            (1) sort by alphabet
                            (2) sort by page number""");
                    int decision = scanner.nextInt();

                    switch (decision) {
                        case 1 -> alphabetSort(terms, "");

                        case 2 -> pageSort(terms, "");
                    }
                }

            }

        }
    }
}

class Term{
    private final String name;
    private Set<Integer> page;
    private final HashMap<String, Term> children;
    public Set<Integer> getPage(){
        return page;
    }
    public void setPage(Set<Integer> page){
        this.page = page;
    }
    public HashMap<String, Term> getChildren() {
        return children;
    }
    public Term(String name, Set<Integer> page){
        this.name = name;
        this.page = page;
        children = new HashMap<>();
    }
    @Override
    public int hashCode(){
        return name.hashCode();
    }
    @Override
    public boolean equals(Object o){
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Term term = (Term) o;
        return name.equals(term.name);
    }
}