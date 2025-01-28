clc;
clear all;

option = input("Distr. model (Normal, Student, Chi2, Fisher)=", "s");

switch option
    case "Normal"
        fprintf("Normal distribution model\n");

        mu = input("mu = \n");
        sigma = input("sigma = \n");

        fprintf("a)\nP(X<=0)=%f\nP(X>=0)=%f\n", normcdf(0, mu, sigma), 1 - normcdf(0, mu, sigma));
        
        fprintf("b)\nP(-1<=X<=1)=%f\n", normcdf(1, mu, sigma) - normcdf(-1, mu, sigma));
        fprintf("P(X<=-1 or X>=1)=%f\n", 1 - normcdf(1, mu, sigma) + normcdf(-1, mu, sigma));

        alpha = input("alpha = \n");
        fprintf("c)x_alpha=%f\n", norminv(alpha, mu, sigma));
        
        beta = input("beta = \n");
        fprintf("d)x_beta=%f\n", norminv(1-beta, mu, sigma));
        
    case "Student"
        fprintf("Student distribution model\n");
        
        n = input("n = \n");
        
        fprintf("a)\nP(X<=0)=%f\nP(X>=0)=%f\n", tcdf(0, n), 1 - tcdf(0, n));
        
        fprintf("b)\nP(-1<=X<=1)=%f\n", tcdf(1, n) - tcdf(-1, n));
        fprintf("P(X<=-1 or X>=1)=%f\n", 1 - tcdf(1, n) + tcdf(-1, n));

        alpha = input("alpha = \n");
        fprintf("c)x_alpha=%f\n", tinv(alpha, n));

        beta = input("beta = \n");
        fprintf("d)x_beta=%f\n", tinv(1-beta, n));

    case "Chi2"
        fprintf("Chi2 distribution model\n");
        
        n = input("n = \n");

        fprintf("a)\nP(X<=0)=%f\nP(X>=0)=%f\n", chi2cdf(0, n), 1 - chi2cdf(0, n));
        
        fprintf("b)\nP(-1<=X<=1)=%f\n", chi2cdf(1, n) - chi2cdf(-1, n));
        fprintf("P(X<=-1 or X>=1)=%f\n", 1 - chi2cdf(1, n) + chi2cdf(-1, n));

        alpha = input("alpha = \n");
        fprintf("c)x_alpha=%f\n", chi2inv(alpha, n));

        beta = input("beta = \n");
        fprintf("d)x_beta=%f\n", chi2inv(1-beta, n));

    case "Fisher"
        fprintf("Fisher distribution model\n");
        
        m = input("m = \n");
        n = input("n = \n");

        fprintf("a)\nP(X<=0)=%f\nP(X>=0)=%f\n", fcdf(0, m, n), 1 - fcdf(0, m, n));
        
        fprintf("b)\nP(-1<=X<=1)=%f\n", fcdf(1, m, n) - fcdf(-1, m, n));
        fprintf("P(X<=-1 or X>=1)=%f\n", 1 - fcdf(1, m, n) + fcdf(-1, m, n));

        alpha = input("alpha = \n");
        fprintf("c)x_alpha=%f\n", tinv(alpha, m, n));

        beta = input("beta = \n");
        fprintf("d)x_beta=%f\n", tinv(1-beta, m, n));

    otherwise
        fprintf("Wrong option");
end