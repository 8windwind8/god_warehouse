package org.example.onlyjava.Controller;

import org.example.onlyjava.Dto.UserLoginDto;
import org.example.onlyjava.Dto.UserRegisterDto;
import org.example.onlyjava.Result.Result;
import org.example.onlyjava.Service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

@RestController

public class UserController {
    @Autowired
    private UserService userService;
    @RequestMapping("/api/login")
    public Result login(@RequestBody UserLoginDto userLoginDto) {
        System.out.println("登录请求");

        return userService.login(userLoginDto.getUsername(), userLoginDto.getPassword());
    }
    @RequestMapping("/api/register")
    public Result register(@RequestBody UserRegisterDto userRegisterDto) {
        System.out.println("注册请求");
        if (!userRegisterDto.getPassword().equals(userRegisterDto.getConfirmPassword())) {
            return Result.error("两次密码不一致");
        }
        userService.register(userRegisterDto.getUsername(), userRegisterDto.getPassword());
        return Result.success("注册成功");
    }


}
