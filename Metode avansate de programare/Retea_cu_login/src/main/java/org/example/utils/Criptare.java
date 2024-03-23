package org.example.utils;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

public class Criptare {
    public static String Cri(String str) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedStr = md.digest(str.getBytes());
        return Base64.getEncoder().encodeToString(hashedStr);
    }
}
