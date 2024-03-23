import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class NumarComplex {
    public double re;
    public double im;
    NumarComplex(double real, double imaginar) {
        this.re = real;
        this.im = imaginar;
    }
    static public NumarComplex fromString(String str) {
        String string_re = "^[-+]?([0-9]+)$";
        String string_im = "^([+-])?(([0-9]*)\\*)?i$";
        String string_re_im = "^([-+]?([0-9]+)(([+-])|$))?([-+]?([0-9]+\\*)?i)?$";

        // numar = a
        Pattern pattern = Pattern.compile(string_re);
        Matcher matcher = pattern.matcher(str);
        if (matcher.find())
        {
            int real = Integer.parseInt(str);
            return new NumarComplex(real, 0);
        }

        // numar = b*i
        pattern = Pattern.compile(string_im);
        matcher = pattern.matcher(str);
        if (matcher.find())
        {
            int imaginar;
            if (str.equals("-i"))
                imaginar = -1;
            else
                if (str.equals("+i") || str.equals("i"))
                    imaginar = 1;
                else {
                    str = str.substring(0, str.length() - 2);
                    imaginar = Integer.parseInt(str);
                }
            return new NumarComplex(0, imaginar);
        }

        // numar = a +/- b*i
        pattern = Pattern.compile(string_re_im);
        matcher = pattern.matcher(str);
        if (matcher.find())
        {
            int imaginar, real;
            String str_real, str_imaginar;
            int poz_semn_separator = Integer.max(str.indexOf('+', 1), str.indexOf('-', 1));
            str_real = str.substring(0, poz_semn_separator);
            str_imaginar = str.substring(poz_semn_separator, str.length());
            if (str_imaginar.equals("-i"))
                imaginar = -1;
            else
                if (str_imaginar.equals("+i"))
                    imaginar = 1;
                else {
                    str_imaginar = str_imaginar.substring(0, str_imaginar.length() - 2);
                    imaginar = Integer.parseInt(str_imaginar);
                }
            real = Integer.parseInt(str_real);
            return new NumarComplex(real, imaginar);
        }

        return null;
    }
    static public NumarComplex adunare(NumarComplex nr1, NumarComplex nr2) {
        NumarComplex rez = new NumarComplex(nr1.re + nr2.re, nr1.im + nr2.im);
        return rez;
    }
    static public NumarComplex scadere(NumarComplex nr1, NumarComplex nr2) {
        NumarComplex rez = new NumarComplex(nr1.re - nr2.re, nr1.im - nr2.im);
        return rez;
    }
    static public NumarComplex inmultire(NumarComplex nr1, NumarComplex nr2) {
        NumarComplex rez = new NumarComplex(nr1.re * nr2.re - nr1.im * nr2.im, nr1.im * nr2.re + nr2.im * nr1.re);
        return rez;
    }
    static public NumarComplex conjugatul(NumarComplex nr) {
        NumarComplex rez = new NumarComplex(nr.re, -1 * nr.im);
        return rez;
    }
    static public NumarComplex impartire(NumarComplex nr1, NumarComplex nr2) {
        NumarComplex conjugat_numitor = NumarComplex.conjugatul(nr2);
        double rez_jos = nr2.re * nr2.re + nr2.im * nr2.im;
        NumarComplex rez_sus = NumarComplex.inmultire(nr1, conjugat_numitor);
        NumarComplex rez = new NumarComplex(rez_sus.re / rez_jos, rez_sus.im / rez_jos);
        return rez;
    }

    @Override
    public String toString() {
        return "re " + this.re + ", im " + this.im;
    }
}
