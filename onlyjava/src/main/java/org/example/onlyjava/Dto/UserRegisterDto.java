package org.example.onlyjava.Dto;

import lombok.Data;
import org.springframework.stereotype.Component;

@Data

public class UserRegisterDto {
    private String username;
    private String password;
    private String confirmPassword;
}
