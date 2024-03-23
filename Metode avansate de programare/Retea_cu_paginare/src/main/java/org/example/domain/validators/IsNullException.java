package org.example.domain.validators;

public class IsNullException extends RuntimeException {
    public IsNullException() {
    }

    public IsNullException(String message) {
        super(message);
    }

    public IsNullException(String message, Throwable cause) {
        super(message, cause);
    }

    public IsNullException(Throwable cause) {
        super(cause);
    }

    public IsNullException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
