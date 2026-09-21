package org.example.onlyjava.Service;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import org.example.onlyjava.Dto.AskDto;
import org.example.onlyjava.Dto.SaveChatDto;
import org.example.onlyjava.Entity.ChatHistoryEntity;
import org.example.onlyjava.Mapper.ChatHistoryMapper;
import org.example.onlyjava.Result.Result;
import org.springframework.ai.chat.client.ChatClient;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;
import org.springframework.ai.deepseek.DeepSeekChatModel;
import tools.jackson.databind.ObjectMapper;

import java.util.List;

@Service
public class AiService {
    @Autowired
    private DeepSeekChatModel deepSeekChatModel;
    @Autowired
    private ChatHistoryMapper chatHistoryMapper;
    @Autowired
    private ObjectMapper objectMapper;

    private final ChatClient chatClient;
    public AiService(ChatClient.Builder builder) {
        this.chatClient = builder.build();
    }


    public Result ask(AskDto askDto) {
        String question = askDto.getQuestion();
        String answer = chatClient.prompt()
                .system("你是一个专业的问答机器人,能够回答用户的问题，每次回答控制在30字以内")
                .user(question)
                .call().content();
        System.out.println(answer);
        return Result.success(answer);
       }

    public Result savechat(SaveChatDto saveChatDto) {
        String username = SecurityContextHolder.getContext()
                .getAuthentication().getName();
        ChatHistoryEntity history = new ChatHistoryEntity();

        try {

            String messagesJson = objectMapper.writeValueAsString(saveChatDto.getMessages());


            history.setId(saveChatDto.getId());
            history.setUsername(username);
            history.setTitle(saveChatDto.getTitle() != null ? saveChatDto.getTitle() : "新对话");
            history.setMessages(messagesJson);


            if (saveChatDto.getId() == null) {
                chatHistoryMapper.insert(history);
                return Result.success(history.getId());
            } else {
                chatHistoryMapper.updateById(history);
                return Result.success(history.getId());
            }
        } catch (Exception e) {
            return Result.error("保存对话失败");
        }



    }

    public Result getchatlist() {
        String username = SecurityContextHolder.getContext()
                .getAuthentication().getName();
        LambdaQueryWrapper<ChatHistoryEntity> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(ChatHistoryEntity::getUsername, username);
        List<ChatHistoryEntity> historyList = chatHistoryMapper.selectList(wrapper);
        return Result.success(historyList);

    }

    public Result deletechat(Long id) {
        chatHistoryMapper.deleteById(id);
        return Result.success("删除成功");
    }

    public Result getchat(Long id) {
        ChatHistoryEntity history = chatHistoryMapper.selectById(id);
        if (history == null) {
            return Result.error("对话不存在");
        }
        try {
            // messages 在数据库里存的是 JSON 字符串，需要反序列化成数组再返回
            List<?> messages = objectMapper.readValue(history.getMessages(), List.class);
            return Result.success(messages);
        } catch (Exception e) {
            return Result.error("解析对话失败");
        }
    }
}
