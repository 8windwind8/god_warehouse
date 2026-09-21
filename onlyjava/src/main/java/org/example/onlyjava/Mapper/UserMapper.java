package org.example.onlyjava.Mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.example.onlyjava.Entity.UserEntity;
import org.apache.ibatis.annotations.Mapper;
@Mapper

public interface UserMapper extends BaseMapper<UserEntity> {
    @Select("select * from user where username = #{username}")
    UserEntity selectByUsername(String username);
}
