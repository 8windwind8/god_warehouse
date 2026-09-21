
import server from '@/Request'


export function login(data) {
    return server({
        url: 'login',
        method: 'POST',
        data
    })
}

export function register(data) {
    return server({
        url: 'register',
        method: 'POST',
        data
    })
}

export function ask(data) {
    return server({
        url: 'ask',
        method: 'POST',
        data
    })
}

export function saveChat(data) {
    return server({
        url: 'savechat',
        method: 'POST',
        data
    })
}

export function getChatList() {
    return server({
        url: 'getchatlist',
        method: 'GET',
        
    })
}

export function deleteChat(id) {
    return server({
        url: `deletechat/${id}`,
        method: 'DELETE',
        
    })
}

export function getChat(id) {
    return server({
        url: `getchat/${id}`,
        method: 'GET',
        
    })
}

