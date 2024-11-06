package com.Application.CreditAdministration.servicesTest;

import com.Application.CreditAdministration.entities.CreditEntity;
import com.Application.CreditAdministration.repositories.CreditRepository;
import com.Application.CreditAdministration.servicies.CreditService;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.dao.DataAccessException;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
public class CreditServiceTest {

    @Mock
    private CreditRepository creditRepository;

    @InjectMocks
    private CreditService creditService;

    @Test
    public void whenGetUserCredits_thenReturnUserCredits() {
        //given
        long userId = 1L;
        ArrayList<CreditEntity> credits = new ArrayList<>();

        //when
        when(creditRepository.findByCreditUserId(userId)).thenReturn(credits);
        ArrayList<CreditEntity> result = creditService.getUserCredits(userId);

        //then
        assertEquals(credits, result);
    }

    @Test
    public void whenGetPhaseCredits_thenReturnPhaseCredits() {
        //given
        int creditPhase = 2;
        ArrayList<CreditEntity> credits = new ArrayList<>();

        //when
        when(creditRepository.findByCreditPhase(creditPhase)).thenReturn(credits);
        ArrayList<CreditEntity> result = creditService.getPhaseCredits(creditPhase);

        //then
        assertEquals(credits, result);
    }

    @Test
    public void whenGetCredit_thenReturnCredit() {
        //given
        long creditId = 1L;
        CreditEntity credit = new CreditEntity();

        //when
        when(creditRepository.findByCreditId(creditId)).thenReturn(credit);
        CreditEntity result = creditService.getCredit(creditId);

        //then
        assertEquals(credit, result);
    }

    @Test
    public void whenSaveCredit_thenReturnSavedCredit() {
        //given
        CreditEntity credit = new CreditEntity();

        //when
        when(creditRepository.save(credit)).thenReturn(credit);
        CreditEntity result = creditService.saveCredit(credit);

        //then
        assertEquals(credit, result);
    }

    @Test
    public void whenUpdateCredit_thenReturnUpdatedCredit() {
        //given
        CreditEntity credit = new CreditEntity();

        //when
        when(creditRepository.save(credit)).thenReturn(credit);
        CreditEntity result = creditService.updateCredit(credit);

        //then
        assertEquals(credit, result);
    }

    @Test
    public void whenDeleteCredit_thenReturnOne() throws Exception {
        //given
        long creditId = 1L;

        //when
        int result = creditService.deleteCredit(creditId);

        //then
        assertEquals(1, result);
        verify(creditRepository).deleteById(creditId);
    }

    @Test
    public void whenDeleteCredit_thenReturnZero() throws Exception {
        //given
        long creditId = 1L;

        //when
        doThrow(new DataAccessException("Database error") {}).when(creditRepository).deleteById(creditId);
        int result = creditService.deleteCredit(creditId);

        //then
        assertEquals(0, result);
        verify(creditRepository, times(1)).deleteById(creditId);
    }

    @Test
    public void whenCreditAmountSimulation_thenReturnSimulatedAmount() {
        //given
        double requestedAmount = 1000000;
        double interest = 5.0;
        int years = 15;

        //when
        double result = creditService.creditAmountSimulation(requestedAmount, interest, years);

        //then
        assertTrue(result > 0);
    }

    @Test
    public void whenRelationCI_thenReturnOneIfBelowThreshold() {
        //given
        double requestedAmount = 1000000;
        double interest = 5.0;
        int years = 15;
        double monthlyEntry = 300000;

        //when
        int result = creditService.relationCI(requestedAmount, interest, years, monthlyEntry);

        //then
        assertEquals(1, result);
    }

    @Test
    public void whenRelationCI_thenReturnZeroIfUnderThreshold() {
        //given
        double requestedAmount = 100000000;
        double interest = 5.0;
        int years = 15;
        double monthlyEntry = 300000;

        //when
        int result = creditService.relationCI(requestedAmount, interest, years, monthlyEntry);

        //then
        assertEquals(0, result);
    }

    @Test
    public void whenRelationDI_thenReturnOneIfBelowThreshold() {
        //given
        double monthlyAmount = 500000;
        double debtsMonthlyAmount = 100000;
        double creditMonthlyAmount = 100000;

        //when
        int result = creditService.relationDI(monthlyAmount, debtsMonthlyAmount, creditMonthlyAmount);

        //then
        assertEquals(1, result);
    }

    @Test
    public void whenRelationDI_thenReturnZeroIfUnderThreshold() {
        //given
        double monthlyAmount = 50000;
        double debtsMonthlyAmount = 100000;
        double creditMonthlyAmount = 100000;

        //when
        int result = creditService.relationDI(monthlyAmount, debtsMonthlyAmount, creditMonthlyAmount);

        //then
        assertEquals(0, result);
    }

    @Test
    public void whenFinalMonthlyAmount_thenReturnFinalMonthlyAmount() {
        //given
        double requestedAmount = 1000000;
        double interest = 5.0;
        int years = 15;

        //when
        double result = creditService.finalMonthlyAmount(requestedAmount, interest, years);

        //then
        assertTrue(result > 0);
    }

    @Test
    public void whenFinalCreditAmount_thenReturnFinalCreditAmount() {
        //given
        double monthlyAmount = 50000;
        int years = 15;
        double requestedAmount = 1000000;

        //when
        double result = creditService.finalCreditAmount(monthlyAmount, years, requestedAmount);

        //then
        assertTrue(result > 0);
    }
}
