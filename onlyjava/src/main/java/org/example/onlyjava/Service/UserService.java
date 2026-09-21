package org.example.onlyjava.Service;

import org.example.onlyjava.Dto.UserRegisterDto;
import org.example.onlyjava.Dto.UserRespose;
import org.example.onlyjava.Entity.UserEntity;
import org.example.onlyjava.Mapper.UserMapper;
import org.example.onlyjava.Result.Result;
import org.example.onlyjava.Utils.JwkTokenUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service
public class UserService {
    @Autowired
    private UserMapper userMapper;
    @Autowired
    private PasswordEncoder passwordEncoder;

    @Autowired
    private JwkTokenUtils jwkTokenUtils;
    private UserRegisterDto userRegisterDto;
    public Result register(String username, String password) {
        UserEntity userEntity = new UserEntity();
        userEntity.setUsername(username);
        userEntity.setPassword(passwordEncoder.encode(password));
        // 查到用户 → 说明已存在 → 报错
        if (userMapper.selectByUsername(username) != null) {
            return Result.error("用户名已存在");
        }
        userMapper.insert(userEntity);
        return Result.success(userEntity);
    }
    public Result login(String username, String password) {
        UserEntity userEntity = userMapper.selectByUsername(username);
       if (userEntity == null) {
            return Result.error("用户名不存在");
        }
        if (!passwordEncoder.matches(password, userEntity.getPassword())) {
            return Result.error("用户名或密码错误");
        }
        // 登录成功
        String token = jwkTokenUtils.generateToken(username);
        UserRespose userRespose = new UserRespose();
        userRespose.setToken(token);
        System.out.println(token);
        return Result.success(userRespose);
    }
}
