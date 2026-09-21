package org.example.onlyjava.Controller;

import org.example.onlyjava.Dto.AskDto;
import org.example.onlyjava.Dto.SaveChatDto;
import org.example.onlyjava.Result.Result;
import org.example.onlyjava.Service.AiService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class AiController {
    @Autowired
    private AiService aiService;

    @RequestMapping("/api/ask")
    public Result ask(@RequestBody AskDto askDto) {
        return aiService.ask(askDto);
    }

    @RequestMapping("/api/savechat")
    public Result savechat(@RequestBody SaveChatDto saveChatDto) {
        return aiService.savechat(saveChatDto);
    }
    @RequestMapping("/api/getchatlist")
    public Result getchatlist() {

        return aiService.getchatlist();
    }
    @RequestMapping("/api/deletechat/{id}")
    public Result deletechat(@PathVariable Long id) {
        return aiService.deletechat(id);
    }
    @RequestMapping("/api/getchat/{id}")
    public Result getchat(@PathVariable Long id) {
        return aiService.getchat(id);
    }
}
