<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'
                xmlns="http://www.w3.org/TR/xhtml1/transitional"
                exclude-result-prefixes="#default">

<!-- $Id -->

<!-- Experimental stylesheet by Dan York
     This is an attempt to replicate the customizations done in ldp.dsl
     Each customization in ldp.dsl is listed in the order in which it
     appears (in ldp.dsl) with the corresponding XSLT template or setting
     below it.  Where there is no XSLT code below an item, that particular
     customization of ldp.dsl is not yet supported here.  Some additional
     options and features have been added and are noted as not being in
     ldp.dsl.  The work on this stylesheet began 5 Jul 2001. -->

<!-- Note that this file, 'ldp-html-common.xsl', is NOT intended to be
     called directly.  Instead, you should call either of two stylesheets:
     'ldp-html.xsl' or 'ldp-html-chunk.xsl'.  The former generates a SINGLE
     HTML file, while the latter performs "chunking" to generate MULTIPLE
     HTML files.  Both of those files import the appropriate Norman Walsh
     stylesheet and then import this customization layer. -->

<!-- NOT IN LDP.DSL - This stylesheet supports the additional use of the
     "role" and "condition" attributes to the <author> tag. The XSLT template
     is listed later in the stylesheet, but the text lables are listed
     here in order to make localization of the stylesheet easier. Note
     that spaces *are* significant in the value, so you should have a
     space after the colon. -->

<xsl:variable name="maintainerlabel">Maintainer: </xsl:variable>
<xsl:variable name="authorlabel">Author: </xsl:variable>


<!-- NOT IN LDP.DSL
     Creates header content in all generated HTML files -->

<xsl:template name="user.head.content">
  <xsl:param name="node" select="."/>
  <meta name="generator" content="Experimental LDP.XSL $Revision$"/>
  <xsl:text>
  </xsl:text>
  <xsl:comment> Generated by LDP XSLT customization layer
      based on Norman Walsh's DocBook XSL stylesheets.
      More information at http://www.linuxdoc.org/ </xsl:comment>
  <xsl:text>
  </xsl:text>

</xsl:template>

<!-- declare-characteristic preserve-sdata?
     No longer appears necessary as it is a JadeTex issue. -->

<!-- generate-legalnotice-link?
     Not currently supported in Norm's XSL stylesheets. Logged
     at SourceForge as a bug. -->

<!-- Should graphics be used for admonitions (notes, warnings)? 0 or 1 -->
<xsl:param name="admon.graphics" select="0"/>

<!-- If using admon graphics (1 above), what is path to graphics?
     Should be the path relative to your document and MUST end with
     a trailing slash.  Also, this parameter needs to be on a
     single line. -->
<xsl:param name="admon.graphics.path">images/</xsl:param>


<!-- Make funcsynopsis look pretty -->
<xsl:param name="funcsynopsis.decoration" select="1" doc:type="boolean"/>

<!-- Extension for HTML files -->
<xsl:param name="html.ext" select="'.html'"/>

<!-- Generate TOCs for book, article, part -->
<xsl:param name="generate.book.toc" select="1" doc:type="boolean"/>
<xsl:param name="generate.article.toc" select="1" doc:type="boolean"/>
<xsl:param name="generate.part.toc" select="1" doc:type="boolean"/>

<!-- generate-book-titlepage -->

<!-- generate-article-titlepage -->

<!-- Equivalent to chunk-skip-first-element-list - forces TOC on separate page
     If 0, first sect is on page for chapter or article -->
<xsl:param name="chunk.first.sections" select="'1'"/>


<!-- NOT IN LDP.DSL -->
<!-- Create chunks for top-level sections. If 0, chunks will only be
     created for chapters/appendixes, and NOT for sectx elements -->
<xsl:param name="chunk.sections" select="'1'"/>

<!-- list-element-list - NO LONGER NEEDED - bug fix -->

<!-- Filename for the root chunk -->
<xsl:param name="root.filename" select="'index'"/>

<!-- shade-verbatim
     I have created a function below that shades the verbatim sections.
     logic would need to be added to check if this is set.
     Norm has added parameters to his 1.44 stylesheets that support
     shading verbatim sections. However, it looks like it requires
     an attribute to a table to have verbatim shading.  Needs to be
     explored further. -->

<!-- When chunking, use id attribute as filename? 0 or 1 -->
<xsl:param name="use.id.as.filename" select="1"/>

<!-- graphic-extensions - NO LONGER NEEDED?? -->

<!-- default graphic filename extension -->
<xsl:param name="graphic.default.extension" select="'.gif'" doc:type="string"/>

<!-- Should chapters be labeled? 0 or 1 -->
<xsl:param name="chapter.autolabel" select="1"/>

<!-- Should sections be labeled? 0 or 1 -->
<xsl:param name="section.autolabel" select="1"/>

<!-- Related to section labels, should those labels include the chapter
     number in them (i.e., 1.1, 1.2, 1.3, 1.4 )-->
<xsl:param name="section.label.includes.component.label" select="1" doc:type="boolean"/>

<!-- To what depth (in sections) should the TOC go? -->
<xsl:param name="toc.section.depth" select="2"/>

<!-- Custom 'emphasis' template to allow 'role="strong"' to
     also produce a bold item. -->
<xsl:template match="emphasis">
  <xsl:choose>
    <xsl:when test="(@role='strong') or (@role='bold')">
      <xsl:call-template name="inline.boldseq"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="inline.italicseq"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<!-- book-titlepage-recto-elements
     article-titlepage-recto-elements
     article-titlepage-recto-mode
     article-title

     - Customizing these elements (for instance, to list what is on the
       title page) involves writing a layer for html/titlepage.templates.xml and the
       other files html/titlepage.xsl and html/titlepage.templates.xsl - Norm
       is doing something funky here and I haven't fully figured it out. -->

<!-- The remainder of ldp.dsl deals with changing the foreground and
     background colors of verbatim elements although in reading through the
     DSSSL it doesn't look like it actually changed the foreground colors.
     The changing of the background shading can be done at two locations
     (one numbered, one not) in the template below. -->

<!-- Custom template for programlisting, screen and synopsis to generate a gray
     background to the item. -->
<xsl:template match="programlisting|screen|synopsis">
  <xsl:param name="suppress-numbers" select="'0'"/>
  <xsl:variable name="vendor" select="system-property('xsl:vendor')"/>
  <xsl:variable name="id"><xsl:call-template name="object.id"/></xsl:variable>

  <xsl:if test="@id">
    <a href="{$id}"/>
  </xsl:if>

  <xsl:choose>
    <xsl:when test="$suppress-numbers = '0'
                    and @linenumbering = 'numbered'
                    and $use.extensions != '0'
                    and $linenumbering.extension != '0'">
      <xsl:variable name="rtf">
        <xsl:apply-templates/>
      </xsl:variable>
      <!-- Change the color bacground color in the line below. -->
      <table border="0" bgcolor="#E0E0E0" width="90%">
      <tr><td>
      <pre class="{name(.)}">
        <xsl:call-template name="number.rtf.lines">
          <xsl:with-param name="rtf" select="$rtf"/>
        </xsl:call-template>
      </pre>
      </td></tr></table>
    </xsl:when>
    <xsl:otherwise>
      <!-- Change the color bacground color in the line below. -->
      <table border="0" bgcolor="#E0E0E0" width="90%">
      <tr><td>
      <pre class="{name(.)}">
        <xsl:apply-templates/>
      </pre>
      </td></tr></table>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<!-- NOT IN LDP.DSL. Custom template to allow Maintainer to be a role in
     the Author element.  It also checks for a "condition" attribute
     to the <author> element. If it finds the condition attribute, it
     copies VERBATIM the value of the attribute to be in front of the
     word Author or Maintainer. This is done to allow maximum flexibility.
     Note that an <xsl:text> element was necessary to put the space
     between the condition and the word Author or Maintainer.  -->

<xsl:template match="author" mode="titlepage.mode">
  <h3 class="{name(.)}">
     <!-- If there is a condition attribute, print it VERBATIM first -->
  <xsl:if test="@condition"><i><xsl:value-of select="@condition"/></i>
  <xsl:text> </xsl:text></xsl:if>
     <!-- Test to see if there is a role. If maintainer, print that. If not,
          assume it is an author. -->
  <xsl:choose>
    <xsl:when test="@role='maintainer'">
        <i><xsl:value-of select="$maintainerlabel"/></i>
    </xsl:when>
    <xsl:otherwise>
        <i><xsl:value-of select="$authorlabel"/></i>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:call-template name="person.name"/>
  </h3>
  <xsl:apply-templates mode="titlepage.mode" select="./contrib"/>
  <xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
</xsl:template>


</xsl:stylesheet>
