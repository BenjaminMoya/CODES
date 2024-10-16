package com.example.demo.entities;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name = "users")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class userEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(unique = true,nullable = false)
    private long userId;

    private String userName;
    private String userRut;
    private String userEmail;
    private String userPassword;
    private int userAge;
    private int userAccountSeniority;
    private int userWorkSeniority;
    private int userSavingCapacity;
    private double userBalance;
    private boolean userIndependent;
    private boolean executive;
}