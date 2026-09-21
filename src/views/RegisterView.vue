<template>
    <div class="container">
        <div class="register">
        <h1>注册</h1>
        <el-form :model="form" ref="formRef" :rules="rules" label-width="120px">
            <el-form-item label="用户名" prop="username">
                <el-input v-model="form.username" placeholder="请输入用户名" :prefix-icon="User"></el-input>
            </el-form-item>
            <el-form-item label="密码" prop="password">
                <el-input v-model="form.password" placeholder="请输入密码" type="password" :prefix-icon="Lock"></el-input>
            </el-form-item>
            <el-form-item label="确认密码" prop="confirmPassword">
                <el-input v-model="form.confirmPassword" placeholder="请确认密码" type="password" :prefix-icon="Lock"></el-input>
            </el-form-item>
            <el-form-item>
                <el-button type="primary" @click="submitForm" class="button" >注册</el-button>
            </el-form-item>
        </el-form>
        <el-link type="primary" @click="router.push('/login')" class="link">已有账号？去登录</el-link>
    </div>

    </div>
</template>
<script setup>
import { ref } from 'vue'
import { register } from '@/Api'
import { ElMessage } from 'element-plus'
import { useRouter } from 'vue-router'
import { User, Lock } from '@element-plus/icons-vue'

const router = useRouter()
const formRef = ref(null)

const form = ref({
    username: '',
    password: '',
    confirmPassword: ''
})

const rules = ref({
    username: [
        { required: true, message: '请输入用户名', trigger: 'blur', min: 3, max: 10 }
    ],
    password: [
        { required: true, message: '请输入密码', trigger: 'blur', min: 6, max: 12 }
    ],
    confirmPassword: [
        { required: true, message: '请确认密码', trigger: 'blur', min: 6, max: 12 }
    ]
})

const submitForm = () => {
    formRef.value.validate().then(() => {
        if (form.value.password !== form.value.confirmPassword) {
            ElMessage.error('两次密码不一致')
            return
        }
        register(form.value).then(res => {
            if (res.code === 200) {
                ElMessage.success('注册成功')
                router.push('/login')
            } else {
                ElMessage.error(res.msg)
            }
        }).catch(() => {
            ElMessage.error('注册失败，请稍后重试')
        })
    }).catch(() => {
        ElMessage.error('请填写完整信息')
    })
    
}
</script>
<style scoped>
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
.register {
  background-color: rgba(255, 255, 255, 0.8);
  padding: 20px;
  border-radius: 10px;
  position: relative;
  height: 40%;
  width: 40%;
  position: absolute;
}
h1 {
    text-align: center;
}
.button {
    margin-top: 10px;
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
