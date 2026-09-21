<template>
  <div class="container">
    <div class="login">
        <h1>登录</h1>
    <el-form :model="form" ref="formRef" :rules="rules" label-width="120px" class="login-form">
        <el-form-item label="用户名" prop="username" class="login-form-item">
            <el-input v-model="form.username" placeholder="请输入用户名" :prefix-icon="User"></el-input>
        </el-form-item>
        <el-form-item label="密码" prop="password" class="login-form-item" >
            <el-input v-model="form.password" placeholder="请输入密码" type="password" :prefix-icon="Lock"></el-input>
        </el-form-item>
        <el-form-item class="login-form-item">
            <el-button type="primary" @click="submitForm" class="button" >登录</el-button>
        </el-form-item>
    </el-form>
    <el-link type="primary" @click="router.push('/register')" class="link">没有账号？去注册</el-link>
  </div>

  </div>
</template>
<script setup>
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { login } from '@/Api'
import { ElMessage } from 'element-plus'
import { User, Lock } from '@element-plus/icons-vue'

const router = useRouter()
const formRef = ref(null)
const TOKEN_KEY = 'token'

const form = ref({
    username: '',
    password: ''
})

const rules = ref({
    username: [
        { required: true, message: '请输入用户名', trigger: 'blur', min: 3, max: 10 }
    ],
    password: [
        { required: true, message: '请输入密码', trigger: 'blur', min: 6, max: 12 }
    ]
})

const submitForm = () => {
    formRef.value.validate().then(() => {
        login(form.value).then(res => {
            if (res.code === 200) {
                ElMessage.success('登录成功')
                setToken(res.data.token)
                router.push('/ai')
            } else {
                ElMessage.error(res.msg)
            }
        }).catch(() => {
            ElMessage.error('登录失败，请稍后重试')
        })
    })
}
const setToken = (token) => {
    localStorage.setItem(TOKEN_KEY, token)
    console.log(token)
}
</script>
<style scoped>
h1 {
    text-align: center;
}
.container {
  background-image: url('@/assets/backimg.jpg');
  background-size: cover;
  left: 9%;
  top: 9%;
  height: 80%;
  width: 80%;
  display: flex;
  justify-content: center;
  align-items: center;
  position: absolute;
}
.login {
  background-color: rgba(255, 255, 255, 0.8);
  padding: 20px;
  border-radius: 10px;
  position: relative;
  height: 40%;
  width: 40%;
  position: absolute;
  
}
.login-form {
    
   
  width: 400px;
}
.login-form-item {
    margin-top: 50px;
}
.button {
    margin-top: -10px;
    text-align: center;
    width: 100px;
    margin-left: 140px;
}
.button:hover {
    color: #409eff;
}
.link {
 color: black;
 
 position: relative;
 top: -50px;
 left: 100px;
}
.link:hover {
    color: #b40b0b;
}
</style>
