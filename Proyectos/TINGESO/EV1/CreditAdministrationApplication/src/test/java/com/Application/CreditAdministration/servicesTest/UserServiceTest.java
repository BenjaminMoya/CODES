package com.Application.CreditAdministration.servicesTest;

import static org.mockito.Mockito.*;
import static org.junit.jupiter.api.Assertions.*;
import com.Application.CreditAdministration.entities.CreditEntity;
import com.Application.CreditAdministration.entities.UserEntity;
import com.Application.CreditAdministration.repositories.CreditRepository;
import com.Application.CreditAdministration.repositories.UserRepository;
import com.Application.CreditAdministration.servicies.UserService;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.dao.DataAccessException;
import org.springframework.test.annotation.Rollback;
import java.util.Arrays;
import java.util.List;

@ExtendWith(MockitoExtension.class)
public class UserServiceTest {

    @Mock
    private UserRepository userRepository;

    @Mock
    private CreditRepository creditRepository;

    @InjectMocks
    private UserService userService;

    @Test
    @Rollback
    public void whenGetUsers_thenReturnUsers(){
        //given
        UserEntity user_1 = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);
        UserEntity user_2 = new UserEntity(1L,"Pedro","12345678-8","email","1234",30,5,10,0,10000000,false,false);
        List<UserEntity> expectedUsers = Arrays.asList(user_1, user_2);

        //when
        when(userRepository.findAll()).thenReturn(expectedUsers);
        List<UserEntity> foundUsers = userService.getUsers();

        //then
        assertEquals(expectedUsers, foundUsers);
        verify(userRepository, times(1)).findAll();
    }

    @Test
    @Rollback
    public void whenSaveUser_thenReturnUser(){
        //given
        UserEntity newUser = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userService.getUserByRut(newUser.getUserRut())).thenReturn(null);
        when(userRepository.save(newUser)).thenReturn(newUser);
        UserEntity result = userService.saveUser(newUser);

        //then
        assertEquals(newUser, result);
        verify(userRepository).save(newUser);
    }

    @Test
    @Rollback
    public void whenSaveUser_thenReturnNull(){
        //given
        UserEntity existingUser = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.findByUserRut(existingUser.getUserRut())).thenReturn(existingUser);
        UserEntity result = userService.saveUser(existingUser);

        //then
        assertNull(result);
        verify(userRepository, never()).save(any(UserEntity.class));
    }

    @Test
    public void whenLogin_thenReturnUser() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.findByUserEmail("email")).thenReturn(user);
        UserEntity result = userService.login("email", "1234");

        //then
        assertNotNull(result);
        assertEquals(user, result);
    }

    @Test
    public void whenLogin_thenReturnNull() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.findByUserEmail("email")).thenReturn(user);
        UserEntity result = userService.login("email", "123");

        //then
        assertNull(result);
    }

    @Test
    public void whenGetUserById_thenReturnUser() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.findByUserId(user.getUserId())).thenReturn(user);
        UserEntity result = userService.getUserById(user.getUserId());

        //then
        assertEquals(user, result);
    }

    @Test
    public void whenGetUserByRut_thenReturnUser() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.findByUserRut(user.getUserRut())).thenReturn(user);
        UserEntity result = userService.getUserByRut(user.getUserRut());

        //then
        assertEquals(user, result);
    }

    @Test
    public void whenGetUserByEmail_thenReturnUser() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.findByUserEmail(user.getUserEmail())).thenReturn(user);
        UserEntity result = userService.getUserByEmail(user.getUserEmail());

        //then
        assertEquals(user, result);
    }

    @Test
    public void whenUpdateUser_thenReturnUpdatedUser() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);

        //when
        when(userRepository.save(user)).thenReturn(user);
        UserEntity result = userService.updateUser(user);

        //then
        assertEquals(user, result);
    }

    @Test
    public void whenDeleteUser_thenReturnOne() throws Exception {
        //given
        Long userId = 1L;

        //when
        doNothing().when(userRepository).deleteById(userId);
        int result = userService.deleteUser(userId);

        //then
        assertEquals(1,result);
    }

    @Test
    public void whenDeleteUser_thenReturnZero() throws Exception {
        //given
        long userId = 1L;

        //when
        doThrow(new DataAccessException("Database error") {}).when(userRepository).deleteById(userId);
        int result = userService.deleteUser(userId);

        //then
        assertEquals(0, result);
        verify(userRepository, times(1)).deleteById(userId);
    }

    @Test
    public void whenZeroSaving_thenReturnOne() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);
        user.setUserSavingCapacity(5);

        //when
        when(userRepository.findByUserId(user.getUserId())).thenReturn(user);
        when(userRepository.save(user)).thenReturn(user);
        int result = userService.zeroSaving(user.getUserId());

        //then
        assertEquals(1, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

    @Test
    public void whenTransferAmount_thenReturnUpdatedBalance() {
        //given
        UserEntity user = new UserEntity(1L,"Benjamin","12345678-9","email","1234",30,5,10,0,10000000,false,false);
        CreditEntity credit = new CreditEntity(2L,1,100000000,1000,120000000,1,20,"27-10-2024",1,"");
        user.setUserBalance(500);

        //when
        when(userRepository.findByUserId(user.getUserId())).thenReturn(user);
        when(creditRepository.findByCreditId(credit.getCreditId())).thenReturn(credit);
        when(userRepository.save(user)).thenReturn(user);
        double result = userService.transferAmount(user.getUserId(), credit.getCreditId());

        //then
        assertEquals(1500, result);
        assertEquals(1500, user.getUserBalance());
    }
}
