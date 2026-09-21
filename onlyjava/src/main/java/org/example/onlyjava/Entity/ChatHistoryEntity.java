package org.example.onlyjava.Entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data

@Builder
@TableName("chat_history")
@NoArgsConstructor
@AllArgsConstructor
public class ChatHistoryEntity {
    @TableId(type = IdType.AUTO)
    private Long id;

    /** 所属用户（从 SecurityContext 拿） */
    private String username;

    /** 会话标题 */
    private String title;

    /** 对话内容（JSON 字符串） */
    private String messages;

    /** 创建时间 */
    private LocalDateTime createTime;

    /** 更新时间 */
    private LocalDateTime updateTime;


}
