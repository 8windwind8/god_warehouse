package org.example.onlyjava.Result;

import lombok.Data;
@Data
public class Result {
    private int code;
    private String msg;
    private Object data;

    public static Result success(Object data) {
        Result r = new Result();
        r.code = 200;
        r.msg = "成功";
        r.data = data;
        return r;
    }

    public static Result error(String msg) {
        Result r = new Result();
        r.code = 500;
        r.msg = msg;
        return r;
    }
    // getter / setter
}
