import { createRouter, createWebHistory } from 'vue-router';

const router = createRouter({

    history: createWebHistory(import.meta.env.BASE_URL),
    routes: [
        {
            path: '/',
            name: 'home',
            component: () => import('../views/loginView.vue'),
            alias: '/inicio',
        },
        {
            path: '/user',
            name: 'user',
            component: () => import('../views/userSolititation.vue'),
            alias: '/inicio',
        }
    ],
});

export default router;