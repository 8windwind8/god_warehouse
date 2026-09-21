package org.example.onlyjava.Dto;

import lombok.Data;

import java.util.List;

@Data
public class SaveChatDto {
    private Long id;

    /** 标题：一般取第一句用户问题 */
    private String title;



    /** 对话内容列表 */
    private List<MessageItem> messages;

    // ===== getter / setter =====
    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public List<MessageItem> getMessages() { return messages; }
    public void setMessages(List<MessageItem> messages) { this.messages = messages; }

    /**
     * 单条消息
     */
    @Data
    public static class MessageItem {
        /** 角色：user / ai */
        private String role;
        /** 内容 */
        private String content;

        public String getRole() { return role; }
        public void setRole(String role) { this.role = role; }

        public String getContent() { return content; }
        public void setContent(String content) { this.content = content; }
    }
}
