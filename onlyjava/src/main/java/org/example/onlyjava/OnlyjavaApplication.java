package org.example.onlyjava;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan
public class OnlyjavaApplication {

    public static void main(String[] args) {
        SpringApplication.run(OnlyjavaApplication.class, args);
    }

}
