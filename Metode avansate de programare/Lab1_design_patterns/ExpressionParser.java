import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressionParser {
    private final String string_re = "^[-+]?([0-9]+)$";
    private final String string_im = "^([+-])?(([0-9]*)\\*)?i$";
    private final String string_re_im = "^([-+]?([0-9]+)(([+-])|$))?([-+]?([0-9]+\\*)?i)?$";
    public boolean verify(String[] args) {
        Pattern pattern = Pattern.compile(string_re_im);
        if (args.length % 2 == 0) {
            System.out.println("Textul dat nu reprezinta o expresie de numere complexe.");
            return Boolean.FALSE;
        }
        for (int i = 0; i < args.length; i ++) {
            if (i % 2 == 0) {
                Matcher matcher = pattern.matcher(args[i]);
                if (!matcher.find()) {
                    System.out.println("Textul dat nu reprezinta o expresie de numere complexe.");
                    return Boolean.FALSE;
                }
            }
            else {
                if (!"+-*/".contains(args[i])) {
                    System.out.println("Textul dat nu reprezinta o expresie de numere complexe.");
                    return Boolean.FALSE;
                }
            }
        }
        return Boolean.TRUE;
    }

    public ArrayList<ComplexExpression> getNumereComplexe(String[] args) {
        ArrayList<ComplexExpression> complexExpressions = new ArrayList<>();
        for (int i = 0; i < args.length; i ++) {
            if (i % 2 == 0) {
                NumarComplex nr = (NumarComplex.fromString(args[i]));
                complexExpressions.add(new StartComplexExpression(nr));
            }
        }
        return complexExpressions;
    }

    public ArrayList<Character> getOperatii(String[] args) {
        ArrayList<Character> operatii = new ArrayList<>();
        for (int i = 0; i < args.length; i ++) {
            if (i % 2 == 1) {
                operatii.add(args[i].charAt(0));
            }
        }
        return operatii;
    }

    public ComplexExpression createExpression(String[] args) {
        ComplexExpressionFactory complexExpressionFactory = ComplexExpressionFactory.getInstance();
        ArrayList<ComplexExpression> complexExpressions = this.getNumereComplexe(args);
        ArrayList<Character> operatii = this.getOperatii(args);
        int i = 0;
        while (i < operatii.size())
        {
            if (operatii.get(i) == '/' || operatii.get(i) == '*')
            {
                ComplexExpression complexExpression = complexExpressionFactory.create(complexExpressions.get(i),
                        complexExpressions.get(i + 1), operatii.get(i));
                complexExpressions.set(i, complexExpression);
                complexExpressions.remove(i + 1);
                operatii.remove(i);
            }
            else {
                i ++;
            }
        }

        i = 0;
        while (operatii.size() >= 1)
        {
            ComplexExpression complexExpression = complexExpressionFactory.create(complexExpressions.get(i),
                        complexExpressions.get(i + 1), operatii.get(i));
            complexExpressions.set(i, complexExpression);
            complexExpressions.remove(i + 1);
            operatii.remove(i);
        }
        return complexExpressions.get(0);
    }
}
