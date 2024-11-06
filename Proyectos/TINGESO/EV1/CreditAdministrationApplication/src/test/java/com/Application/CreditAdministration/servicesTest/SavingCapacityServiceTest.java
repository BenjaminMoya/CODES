package com.Application.CreditAdministration.servicesTest;

import com.Application.CreditAdministration.entities.UserEntity;
import com.Application.CreditAdministration.repositories.UserRepository;
import com.Application.CreditAdministration.servicies.SavingCapacityService;
import com.Application.CreditAdministration.servicies.UserService;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class SavingCapacityServiceTest {

    @Mock
    private UserRepository userRepository;

    @Mock
    private UserService userService;

    @InjectMocks
    private SavingCapacityService savingCapacityService;

    @Test
    public void whenMinAmount_thenReturnOne() {
        //given
        long userId = 1L;
        double creditAmount = 1000;
        UserEntity user = new UserEntity();
        user.setUserBalance(150);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.minAmount(userId, creditAmount);

        //then
        assertEquals(1, result);
        assertEquals(1, user.getUserSavingCapacity());
        verify(userService).updateUser(user);
    }

    @Test
    public void whenMinAmount_thenReturnZero() {
        //given
        long userId = 1L;
        double creditAmount = 1000;
        UserEntity user = new UserEntity();
        user.setUserBalance(0);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.minAmount(userId, creditAmount);

        //then
        assertEquals(0, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

    @Test
    public void whenSavingHistoryAndGreatRetirementFalse_thenReturnOne() {
        //given
        long userId = 1L;
        boolean greatRetirement = false;
        UserEntity user = new UserEntity();
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.savingHistory(userId, greatRetirement);

        //then
        assertEquals(1, result);
        assertEquals(1, user.getUserSavingCapacity());
        verify(userService).updateUser(user);
    }

    @Test
    public void whenSavingHistoryAndGreatRetirementTrue_thenReturnZero() {
        // given
        long userId = 1L;
        boolean greatRetirement = true;
        UserEntity user = new UserEntity();
        user.setUserSavingCapacity(0);

        // when
        int result = savingCapacityService.savingHistory(userId, greatRetirement);

        // then
        assertEquals(0, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

    @Test
    public void whenPeriodicDepositIsPeriodicAndDepositValid_thenReturnOne() {
        //given
        long userId = 1L;
        double monthlyDeposit = 10;
        double monthlyEntry = 100;
        boolean isPeriodic = true;
        UserEntity user = new UserEntity();
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.periodicDeposit(userId, monthlyDeposit, monthlyEntry, isPeriodic);

        //then
        assertEquals(1, result);
        assertEquals(1, user.getUserSavingCapacity());
        verify(userService).updateUser(user);
    }

    @Test
    public void whenPeriodicDepositIsNotPeriodicAndDepositValid_thenReturnZero() {
        //given
        long userId = 1L;
        double monthlyDeposit = 10;
        double monthlyEntry = 100;
        boolean isPeriodic = false;
        UserEntity user = new UserEntity();
        user.setUserSavingCapacity(0);

        //when
        int result = savingCapacityService.periodicDeposit(userId, monthlyDeposit, monthlyEntry, isPeriodic);

        //then
        assertEquals(0, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

    @Test
    public void whenRelationSAAndSeniorityLessThan2_thenReturnOne() {
        //given
        long userId = 1L;
        double creditAmount = 500;
        UserEntity user = new UserEntity();
        user.setUserAccountSeniority(1);
        user.setUserBalance(150);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.relationSA(userId, creditAmount);

        //then
        assertEquals(1, result);
        assertEquals(1, user.getUserSavingCapacity());
        verify(userService).updateUser(user);
    }

    @Test
    public void whenRelationSAAndSeniorityLessThan2_thenReturnZero() {
        //given
        long userId = 1L;
        double creditAmount = 50000000;
        UserEntity user = new UserEntity();
        user.setUserAccountSeniority(1);
        user.setUserBalance(150);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.relationSA(userId, creditAmount);

        //then
        assertEquals(0, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

    @Test
    public void whenRelationSAAndSeniorityGreaterThan2_thenReturnOne() {
        //given
        long userId = 1L;
        double creditAmount = 500;
        UserEntity user = new UserEntity();
        user.setUserAccountSeniority(3);
        user.setUserBalance(100);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.relationSA(userId, creditAmount);

        //then
        assertEquals(1, result);
        assertEquals(1, user.getUserSavingCapacity());
        verify(userService).updateUser(user);
    }

    @Test
    public void whenRelationSAAndSeniorityGreaterThan2_thenReturnZero() {
        //given
        long userId = 1L;
        double creditAmount = 50000000;
        UserEntity user = new UserEntity();
        user.setUserAccountSeniority(3);
        user.setUserBalance(100);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.relationSA(userId, creditAmount);

        //then
        assertEquals(0, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

    @Test
    public void whenRecentOutAndBalanceGreaterThanMaxRetirement_thenReturnOne() {
        //given
        long userId = 1L;
        double maxRetirement = 50;
        UserEntity user = new UserEntity();
        user.setUserBalance(200);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.recentOut(userId, maxRetirement);

        //then
        assertEquals(1, result);
        assertEquals(1, user.getUserSavingCapacity());
        verify(userService).updateUser(user);
    }

    @Test
    public void whenRecentOutAndBalanceGreaterThanMaxRetirement_thenReturnZero() {
        //given
        long userId = 1L;
        double maxRetirement = 5000000;
        UserEntity user = new UserEntity();
        user.setUserBalance(200);
        user.setUserSavingCapacity(0);

        //when
        when(userRepository.findByUserId(userId)).thenReturn(user);
        int result = savingCapacityService.recentOut(userId, maxRetirement);

        //then
        assertEquals(0, result);
        assertEquals(0, user.getUserSavingCapacity());
    }

}
