package org.example.onlyjava.Entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.stereotype.Component;

import java.time.LocalDate;
import java.time.LocalDateTime;
@Data

@Builder
@TableName("user")
@NoArgsConstructor
@AllArgsConstructor

public class UserEntity {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String username;
    private String password;



        // 用户ID


//    /**
//     * 是否为普通用户
//     */
//    public boolean isUser() {
//        return UserType.USER.getCode().equals(this.userType);
//    }

        /**
         * 是否为正常状态
         */

//
//    /**
//     * 是否被禁用
//     */
//    public boolean isDisabled() {
//        return UserStatus.DISABLED.getCode().equals(this.status);
//    }
//
        /**
         * 获取显示名称（优先显示昵称，否则显示用户名）
         */

        /**
         * 获取用户类型显示名称
         */

        /**
         * 获取用户状态显示名称
         */





}
