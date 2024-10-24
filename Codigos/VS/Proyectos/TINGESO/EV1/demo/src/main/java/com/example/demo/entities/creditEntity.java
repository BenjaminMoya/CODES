package com.example.demo.entities;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;
import java.util.Date;

@Entity
@Table(name = "credits")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class creditEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(unique = true,nullable = false)
    private long creditId;

    private long creditUserId;
    private double creditPropertyAmount;
    private double creditRequestedAmount;
    private int creditPhase;
    private int creditTerm;
    private Date creditInitDate;

    // Primera = 1, Segunda = 2, Comercial = 3, Remodelacion = 4
    private int creditType;
    private boolean latePayment;
    private double maxAmount;
}
