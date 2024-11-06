import { createRouter, createWebHistory } from 'vue-router';

const router = createRouter({

    history: createWebHistory(import.meta.env.BASE_URL),
    routes: [
        {
            path: '/',
            name: 'home',
            component: () => import('../views/anonMain.vue'),
            alias: '/inicio',
        },
        {
            path: '/login',
            name: 'login',
            component: () => import('../views/loginView.vue'),
            alias: '/inicio',
        },
    ],
});

export default router;