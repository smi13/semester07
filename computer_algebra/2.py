R2.<x1, x2, x3, x4, y1, y2, y3, y4, y5> = PolynomialRing(QQ, 9, order = 'lex')
I2 = ideal(y1 - x1 * x3^2,
           y2 - x2^5,
           y3 - x1^2 * x2^3,
           y4 - x3^3 * x4,
           y5 - x2 * x4^2)
B2 = I2.groebner_basis()
print "Groebner basis:"
for b in B2:
    print b

print "\nToric ideal basis:"
for b in B2:
    if set(b.variables()).intersection([x1, x2, x3, x4]) == set():
        print b
